// control+c from zt zSingleton.h

#ifndef _GROM_SINGLETON_H__
#define _GROM_SINGLETON_H__

#include "gorm_sys_inc.h"
template <typename T > 
class GORM_Singleton
{
private:
	/**
	 * \brief 拷贝构造函数，没有实现，禁用掉了
	 *
	 */
	GORM_Singleton(const GORM_Singleton&);

	/**
	 * \brief 赋值操作符号，没有实现，禁用掉了
	 *
	 */
	const GORM_Singleton & operator= (const GORM_Singleton &);
protected:

	GORM_Singleton( void )
	{
	}

	virtual ~GORM_Singleton( void )
	{
	    this->m_pInstance = nullptr;					
	}

public:
	static T* Instance( void )
	{
		return m_pInstance.get();
	}

	static T& GetMe(void)
	{
		return *(Instance().get());
	}

	static shared_ptr<T> SharedPtr()
	{
	    return m_pInstance;
	}

	static shared_ptr<T> m_pInstance;

};

template <typename T>
shared_ptr<T> GORM_Singleton<T>::m_pInstance = make_shared<T>();

#endif
