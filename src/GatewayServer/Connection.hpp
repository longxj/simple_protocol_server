#ifndef __CONNECTION_HPP
#define __CONNECTION_HPP

class CConnection
{
private:
	int m_iSockID;

public:
	const int GetSocketID() const { return m_iSockID; }
	void SetSocketID(const int iSocketID) { m_iSockID = iSocketID; }
};

#endif
