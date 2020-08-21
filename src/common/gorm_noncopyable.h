// control+c from zt zNoncopyable.h 

#ifndef _GORM_Noncopyable_h__
#define _GORM_Noncopyable_h__

/**
 * \brief 使所有的子类禁用拷贝构造函数和赋值符号
 *
 */
class GORM_Noncopyable
{

	protected:

		/**
		 * \brief 缺省构造函数
		 *
		 */
		GORM_Noncopyable() {};

		/**
		 * \brief 缺省析构函数
		 *
		 */
		virtual ~GORM_Noncopyable() {};

	private:

		/**
		 * \brief 拷贝构造函数，没有实现，禁用掉了
		 *
		 */
		GORM_Noncopyable(const GORM_Noncopyable&);

		/**
		 * \brief 赋值操作符号，没有实现，禁用掉了
		 *
		 */
		const GORM_Noncopyable & operator= (const GORM_Noncopyable &);

};

#endif


