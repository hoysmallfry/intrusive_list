#ifndef DEFINE_ITERATOR_HPP
#define DEFINE_ITERATOR_HPP

#include <iterator>
#include "intrusive/list_hook.hpp"

namespace intrusive
{
	template <typename T, typename Distance = ptrdiff_t,
		typename Pointer = T*, typename Reference = T&>
	struct define_list_iterator
	{
		class type :
			std::iterator<std::bidirectional_iterator_tag, T, Distance, Pointer, Reference>
		{
		public:
			// default constructor
			type() :
			  mData(nullptr)
			  {}

			  // assignment constructor
			  type(list_base_hook* pData) :
			  mData(pData)
			  {}

			  // copy constructor
			  type(iterator& pCopy) :
			  mData(pCopy.mData)
			  {}

			  // assignment operator
			  type& operator= (iterator& pAssign)
			  {
				  mData = pAssign.mData;
			  }

			  // prefix increment operator.
			  type& operator++()
			  {
				  do_increment();
				  return *this;
			  }
			  // postfix increment operator.
			  type operator++(int)
			  {
				  do_increment();
				  return *this;
			  }

			  // prefix decrement operator.
			  type& operator--()
			  {
				  do_decrement();
				  return *this;
			  }
			  // postfix decrement operator.
			  type operator--(int)
			  {
				  do_decrement();
				  return *this;
			  }

			  // equality operator.
			  bool operator == (const type& pSecond)
			  {
				  return mData == pSecond.mData;
			  }
			  // inequality operator.
			  bool operator != (const type& pSecond)
			  {
				  return mData != pSecond.mData;
			  }

			  // rvalue deference operators.
			  const reference operator* () const
			  {
				  return safe_reference();
			  }
			  const pointer operator->() const 
			  {
				  return &safe_reference();
			  }

			  // lvalue deference operators.
			  reference operator* ()
			  {
				  return safe_reference();
			  }
			  pointer operator->()
			  {
				  return &safe_reference();
			  }

		private:
			void do_increment()
			{
				mData = safe_reference().mNext;
			}

			void do_decrement()
			{
				mData = safe_reference().mPrevious;
			}

			reference safe_reference()
			{
				// check for initialization.
				if(!mData)
					throw std::exception("Iterator not initialized.");

				// if the dynamic cast fails, its because it hit a pointer that was not proper.
				try
				{
					return dynamic_cast<reference&>(*mData);
				}
				catch (const std::bad_cast&)
				{
					throw std::exception("Iterator out of range.");
				}
			}

			list_base_hook* mData;
		};
	};
}

#endif
