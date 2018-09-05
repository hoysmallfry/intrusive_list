#ifndef INTRUSIVE_LIST_HOOK_HPP
#define INTRUSIVE_LIST_HOOK_HPP

namespace intrusive
{
	// used to determine what the hook does when it is linked and unlinked.
	namespace link_mode
	{
		enum type
		{
			normal_link,
			safe_link,
			auto_unlink
		};
	}

	struct list_base_hook
	{
	public:
		typedef list_base_hook* pointer;

		list_base_hook();
		virtual ~list_base_hook();

		virtual void unlink();

		pointer mNext;
		pointer mPrevious;
	};

	template <typename Tag = void>
	class list_hook :
		public list_base_hook
	{
	public:
		typedef Tag tag_type;

		typedef list_hook* pointer;

		~list_hook()
		{
			if(mLinked)
				unlink();
		}

		bool is_linked() const
		{
			return mLinked;
		}

		void unlink()
		{
			if(!mLinked)
				throw std::exception("Node not in intrusive list.");

			list_base_hook::unlink();
			mLinked = false;
		}

	protected:
		list_hook() :
		mLinked(false)
		{}

	private:
		bool mLinked;

		// friend that can access next and previous pointers.
		template <typename Data, typename Tag>
		friend class list;
	};
} 

#endif
