#pragma once


#define SHARED(TYPE)	std::shared_ptr<TYPE>
#define UNIQUE(TYPE)	std::unique_ptr<TYPE>


#define GENERATED_BODY(CLASS, SUPER) \
	public: \
		virtual std::string __GetClassName() const override \
		{ \
			return std::string(#CLASS); \
		} \
		\
		using Super = SUPER;