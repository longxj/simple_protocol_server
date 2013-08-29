#ifndef MY_QUEUE_HPP_
#define MY_QUEUE_HPP_

#include <stdint.h>
#include <stddef.h>

static const CACHE_LEN = 64;

template<class DataType>
class RingBuffer
{
public:
	RingBuffer()
		{
			mask_ = 0;
			buffer_ = NULL;
		}

	~RingBuffer()
		{
			delete buffer_;
		}

	bool Init(uint64_t capacity)
		{
			if (capacity == 0)
			{
				return false;
			}

			// 大小为2的整数倍
			for (mask_ = 1; mask_ < capacity; mask_ <<= 1)

			buffer_ = new DataType[mask_];
			mask_ -= 1;

			return true;
		}

	// 线程安全
public:
	inline void GetData(uint64_t index, DataType& data)
		{
			data = buffer_[index & mask_];
		}

	
	inline void SetData(uint64_t index, const DataType& data)
		{
			buffer_[index & mask_] = data;
		}

	inline DataType* GetSlot(uint64_t index)
		{
			return &buffer_[index & mask_];
		}
	
	inline uint64_t Capacity()
		{
			return mask_ + 1;
		}
			
private:
	DataType* buffer_;
	uint64_t mask_;
};

template<class DataType>
class IConsumer
{
	// 阻塞接口
public:
	virtual void Consume(DataType& data) = 0;

	virtual DataType* GetSlot() = 0;
	virtual void Commit() = 0;	
};

template<class DataType>
class IProducer
{
	// 阻塞接口
public:
	virtual void Produce(const DataType& data) = 0;

	virtual DataType* GetSlot() = 0;
	virtual void Commit() = 0;
};

template<class DataType>
class IQueue
{
public:
	virtual IConsumer* GetConsumer() = 0;
	virtual IProducer* GetProducer() = 0;
};

template<class DataType>
class SPSCConsumer : public IConsumer
{
public:
	SPSCConsumer()
		{
			pos_ = 0;
			queue_ = NULL;
		}
	
	void Init(SPSCQueue<DataType>& queue_)
		{
			queue_ = &queue;
		}
	
public:
	virtual void Consume(DataType& data)
		{
			WaitForReady();
			
			queue_->GetData(pos_, data);
			pos_++;
		}

	virtual DataType* GetSlot()
		{
			WaitForReady();

			return queue_->GetSlot(pos_);
		}
	
	virtual void Commit()
		{
			pos_++;
		}

	inline uint64_t pos()
		{
			return pos_;
		}

private:
	inline void WaitForReady()
		{
			while (pos_ >= end_cache_)
			{
				UpdateEndCache();
			}
		}
	
	inline void UpdateEndCache()
		{
			end_cache_ = queue->GetProducerPos();
		}

private:
	volatile uint64_t pos_ __attribute__((aligned(CACHE_LEN)));
	uint64_t end_cache_ __attribute__((aligned(CACHE_LEN)));
	SPSCQueue<DataType>* queue_;
};

template<class DataType>
class SPSCProducer : public IProducer
{
	// block: 需要保证线程安全
public:
	virtual void Produce(const DataType& data)
		{
			WaitForReady();
			
			queue_->SetData(pos_, data);
			asm volatile("sfence":::"memory");
			pos_++;
		}

	virtual DataType* GetSlot()
		{
			WaitForReady();
			
			return queue->GetSlot(pos_);
		}

	virtual void Commit()
		{
			asm volatile("sfence":::"memory");
			pos_++;
		}

	inline uint64_t pos()
		{
			return pos_;
		}

	// block: 不需要保证线程安全
public:
	SPSCProducer()
		{
			pos_ = 0;
			queue_ = NULL;
		}
	
	void Init(SPSCQueue<DataType>& queue)
		{
			queue_ = &queue;
			UpdateEndCache();
		}

private:
	inline void WaitForReady()
		{
			while (pos_ >= end_cache_)
			{
				UpdateEndCache();
			}
		}
	
	inline void UpdateEndCache()
		{
			end_cache_ = queue->GetConsumerPos() + queue->GetCapacity();
		}

private:
	volatile uint64_t pos_ __attribute__((aligned(CACHE_LEN)));
	uint64_t uint64_t end_cache_ __attribute__((aligned(CACHE_LEN)));
	SPSCQueue<DataType>* queue_;
};

template<class DataType>
class SPSCQueue : public IQueue
{
public:
	SPSCQueue()
		{
			consumer_count_ = 0;
			producer_count_ = 0;
		}

	bool Init(uint64_t capacity)
		{
			if (!buffer_.Init(capacity))
			{
				return false;
			}

			// 必须在buffer_之后
			producer_.Init(*this);
			consumer_.Init(*this);
		}

	IConsumer* GetConsumer()
		{
			if (consumer_count_ < 1)
			{
				consumer_count_++;
				return &consumer_;
			}
			else
			{
				return NULL;
			}
		}

	IProducer* GetProducer()
		{
			if (producer_count_ < 1)
			{
				producer_count_++;
				return &producer_;
			}
			else
			{
				return NULL;
			}
		}

	// 线程安全
public:
	inline uint64_t Capacity()
		{
			return buffer_.Capacity();
		}

	// 非实时数据
	inline uint64_t Size()
		{
			return producer_.pos() - consumer_.pos();
		}

	// 非实时
	inline uint64_t GetConsumerPos()
		{
			return consumer_.pos();
		}

	// 非实时
	inline uint64_t GetProducerPos()
		{
			return producer_.pos();
		}

	inline void GetData(uint64_t index, DataType& data)
		{
			buffer_.GetData(index, data);
		}

	inline void SetData(uint64_t index, const DataType& data)
		{
			buffer_.SetData(index, data);
		}

	inline DataType* GetSlot(uint64_t index)
		{
			return buffer_.GetSlot(index);
		}

private:
	RingBuffer<DataType> buffer_;
	SPSCConsumer consumer_;
	uint8_t consumer_count_;
	SPSCProducer producer_;
	uint8_t producer_count_;
};


#endif
