#include "list_hook.hpp"

namespace intrusive
{
	list_base_hook::~list_base_hook()
	{}

	void list_base_hook::unlink()
	{
		mPrevious->mNext = mNext;
		mNext->mPrevious = mPrevious;
		
		// remove connections.
		mNext = nullptr;
		mPrevious = nullptr;
	}

	list_base_hook::list_base_hook() :
	mNext(nullptr),
	mPrevious(nullptr)
	{}
} 
