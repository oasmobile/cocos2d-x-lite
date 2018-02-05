#ifndef CALL_WITH_CONTEXT_H
#define CALL_WITH_CONTEXT_H

#include <utility>
#include <map>
#include <type_traits>

namespace cribt
{
	template <typename T>
	struct identity
	{
		using type = T;
	};

	template <std::size_t ... Indexies>
	struct index_sequence
	{};

	template <std::size_t Current, typename CurrentIndexies = index_sequence<> >
	struct make_index_sequence_impl;

	template <std::size_t ... Indexies>
	struct make_index_sequence_impl<0, index_sequence<Indexies ...> >
		:    identity<index_sequence<Indexies ...> >
	{};

	template <std::size_t Current, std::size_t ... Indexies>
	struct make_index_sequence_impl<Current, index_sequence<Indexies ...> >
		:    make_index_sequence_impl<Current - 1, index_sequence<Current - 1, Indexies ...> >
	{};

	template <class ... T>
	using index_sequence_for = typename make_index_sequence_impl<sizeof ... (T)>::type;

	template <typename Context, typename ... Args, std::size_t ... Indexies>
	inline void
	call_with_context_impl(
		const Context& ctx,
		void   (* f)( Args ... ),
		index_sequence<Indexies ...>
	) {
		f( ctx.get_arg( identity<Args>{}, Indexies ) ... );
		ctx.set_result();
	}
	
	template <typename Context, typename Result, typename ... Args, std::size_t ... Indexies>
	inline void
	call_with_context_impl(
		const Context& ctx,
		Result   (* f)( Args ... ),
		index_sequence<Indexies ...>
	) {
		Result res = f( ctx.get_arg( identity<Args>{}, Indexies ) ... );
		ctx.set_result(res);
	}

	template <typename Context, typename Result, typename ... Args>
	inline bool
	call_with_context(
		const Context& ctx,
		Result (* f)( Args ... )
	) {
		call_with_context_impl( ctx, f, index_sequence_for<Args ...>{});
		return true;
	}
	
	template <typename Context, typename T, typename ... Args, std::size_t ... Indexies>
	inline void
	call_with_context_impl(
		const Context& ctx,
		void   (T::* f)( Args ... ),
		void *ptr,
		index_sequence<Indexies ...>
	) {
		T* obj = (T*)ptr;
		(obj->*f)( ctx.get_arg( identity<Args>{}, Indexies ) ... );
		ctx.set_result();
	}
	
	template <typename Context, typename T, typename Result, typename ... Args, std::size_t ... Indexies>
	inline void
	call_with_context_impl(
		const Context& ctx,
		Result (T::* f)( Args ... ),
		void *ptr,
		index_sequence<Indexies ...>
	) {
		T* obj = (T*)ptr;
		Result res = (obj->*f)( ctx.get_arg( identity<Args>{}, Indexies ) ... );
		ctx.set_result(res);
	}

	template <typename Context, typename T, typename Result, typename ... Args>
	inline bool
	call_with_context(
		const Context& ctx,
		Result (T::* f)( Args ... ),
		void *ptr
	) {
		call_with_context_impl( ctx, f, ptr, index_sequence_for<Args ...>{});
		return true;
	}
	
	template <typename Context, typename T, typename ... Args, std::size_t ... Indexies>
	inline void
	call_with_context_impl(
		const Context& ctx,
		void   (T::* f)( Args ... ) const,
		void *ptr,
		index_sequence<Indexies ...>
	) {
		T* obj = (T*)ptr;
		(obj->*f)( ctx.get_arg( identity<Args>{}, Indexies ) ... );
		ctx.set_result();
	}
	
	template <typename Context, typename T, typename Result, typename ... Args, std::size_t ... Indexies>
	inline void
	call_with_context_impl(
		const Context& ctx,
		Result (T::* f)( Args ... ) const,
		void *ptr,
		index_sequence<Indexies ...>
	) {
		T* obj = (T*)ptr;
		Result res = (obj->*f)( ctx.get_arg( identity<Args>{}, Indexies ) ... );
		ctx.set_result(res);
	}

	template <typename Context, typename T, typename Result, typename ... Args>
	inline bool
	call_with_context(
		const Context& ctx,
		Result (T::* f)( Args ... ) const,
		void *ptr
	) {
		call_with_context_impl( ctx, f, ptr, index_sequence_for<Args ...>{});
		return true;
	}

	template <typename Result, typename ... Args>
	inline int get_arguments_count(
		Result (* f)( Args ... )
	) {
		return sizeof...(Args);
	}
	
	template <typename T, typename Result, typename ... Args>
	inline int get_arguments_count(
		Result (T::* f)( Args ... )
	) {
		return sizeof...(Args);
	}

	template <typename T, typename Result, typename ... Args>
	inline int get_arguments_count(
		Result (T::* f)( Args ... ) const
	) {
		return sizeof...(Args);
	}
}    // END: namespace (cribt)

#endif