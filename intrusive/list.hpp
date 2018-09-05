#ifndef INTRUSIVE_LIST_HPP
#define INTRUSIVE_LIST_HPP

#include <exception>
#include <ostream>
#include "intrusive/list_hook.hpp"
#include "define_iterator.hpp"

namespace intrusive
{
	template <typename Data, typename Tag = void>
	class list
	{
	public:

		typedef Data data_type;

		typedef typename define_list_iterator<Data>::type iterator;

		list()
		{
			// the sentinel begins pointing to itself at both ends.
			mSentinel.mNext = mSentinel.mPrevious = &mSentinel;
		}

		void push_back(list_hook<Tag>& pNewNode)
		{
			// throw error if already linked in.
			if(pNewNode.mLinked)
				throw std::exception("Node already in intrusive list.");

			do_push_back(pNewNode);
			pNewNode.mLinked = true;
		}

		void remove(list_hook<Tag>& pHook)
		{
			pHook.unlink();
		}

		iterator begin()
		{
			return iterator(mSentinel.mNext);
		}

		iterator end()
		{
			return iterator(&mSentinel);
		}

		bool empty()
		{
			return mSentinel.mNext == &mSentinel && mSentinel.mPrevious == &mSentinel;
		}

	private:

		void do_push_back(list_hook<Tag>& pNewNode)
		{
			// cache the pointer to the hook
			auto newNodePtr = &pNewNode;

			// hook the new node to the end of the list.
			mSentinel.mPrevious->mNext = newNodePtr;
			pNewNode.mPrevious = mSentinel.mPrevious;

			// make the new node the tail.
			pNewNode.mNext = &mSentinel;
			mSentinel.mPrevious = newNodePtr;
		}

		list_base_hook mSentinel;
	};


	// standard compliant insertion operator prints out a list given.
	template <typename Data, typename Tag>
	std::ostream& operator << (std::ostream& pStream, list<Data, Tag>& pList)
	{
		if(!pStream)
			throw std::exception("Bad stream.");

		if (pList.empty())
		{
			pStream << "empty";
		}
		else
		{
			for(auto iter = pList.begin(); iter != pList.end(); ++iter)
				pStream << *iter << " ";
		}

		return pStream;
	}
}

#endif
