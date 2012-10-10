#ifndef __SHAREMEMORY_HPP
#define __SHAREMEMORY_HPP

#include <assert.h>
#include <sys/ipc.h>
#include <sys/shm.h>

class CShareMemory
{
private:
	unsigned int m_uiSize;
	char* m_pCur; //current free memory point
	key_t m_iShmId;

public:
	key_t GetShmId() {return m_iShmId;}
	void SetShmId(key_t iShmId) {m_iShmId = iShmId;}
	
	void SetMemAddr(char* pAddr) {m_pCur = pAddr;}
	
	unsigned int GetSize() {return m_uiSize;}
	void SetSize(unsigned int uiSize) {m_uiSize = uiSize;}
			
	unsigned int GetFreeSize()
	{
		unsigned int uiUsedSize = m_pCur - (char*)this - sizeof(CShareMemory);
		assert(m_uiSize >= uiUsedSize);
		return m_uiSize - uiUsedSize;
	}

	void* AllocateMem(unsigned int uiSize)
	{
		if (uiSize > GetFreeSize())
		{
			return NULL;
		}

		void* pRt = m_pCur;
		m_pCur += uiSize;
		return pRt;
	}

	/*
	 * @create a shm if exist resume the shm
	 * @author seanlong
	 * @param[in] iKey shm key
	 * @param[in] iSize shm size
	 * @return a CShareMemory obj if success or NULL if fail. errno has been set
	 */       
	static CShareMemory* CreateShm(key_t iKey, size_t iSize)
	{
		size_t iTotalSize = iSize + sizeof(CShareMemory);
		int iShmId = shmget(iKey, iTotalSize, 0666 | IPC_CREATE | IPC_EXCL);

		bool bExist = false;
		if (iShmId < 0)
		{
			if (errno != EEXIST)
			{
				return NULL;
			}
			else //shmmem exist
			{
				iShmId = shmget(iKey, iTotalSize, 0666);
				if (iShmId < 0)
				{
					return NULL;
				}
				bExist = true;
			}				
		}

		CShareMemory* pShareMemory = shmat(iKey, 0, 0);
		if (pShareMemory < 0)
		{
			return NULL;
		}

		//depends on bExist to init CShareMemory
		if (!bExist)
		{
			//new shm
			pShareMemory->SetSize(iSize);
			pShareMemory->SetMemAddr((char*)pShareMemory + sizeof(CShareMemory));
			pShareMemory->SetShmId(iShmId);
		}

		//if existed shm, nothing to do
		return (CShareMemory*)pShareMemory;
	}

	int Destroy()
	{
		//detach first
		void* pAddr = shmdt(this);
		if (pAddr < 0)
		{
			return errno;
		}

		//rm shm
		if (shmctl(m_iShmId, IPC_RMID, 0) < 0)
		{
			return errno;
		}

		return 0;
	}		
};

#endif
