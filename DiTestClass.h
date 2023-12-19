#ifndef __DI_TEST_CLASS_H__
#define __DI_TEST_CLASS_H__

#include <string_view>

namespace di
{
	namespace test
	{
		/*
		
		Below we have some of the coding guidelines for the library, and a test class to be copied as a "fast class template".
		Please refer to the "readme.md" file, to have the complete coding guidelines.

		*/

		//Everything is explicitly deleted in the 'TestClass', you can copy it and implement what do you need (you may do your job faster without forgetting anything).
		//In polymorphic base classes, you may need the virtual destructor(you have to delete the 'normal destructor' and start working).

		//Attributes (tested on MSVC, C++ standard -> C20, MAY NOT work). Still :
		//For "void return-type methods" please ALWAYS use the [[NORETURN]] attribute.
		//In case you want to force the user use the return value , please ALWAYS use [[NODISCARD]] (VERY IMPORTANT if we use 'std::move(some_unique_pointer)' to transfer ownership)
		//Extra 1: Prefer std::string_view over std::string when you need a read-only string, especially for function parameters.
		//Extra 2 (but maybe bad practice) : If you don't want to initialize some data members please ALWAYS use [[MAYBE_UNUSED]].
		//Example : If we have a struct, and we want to fill it with some bytes of data(using memcpy or std::copy), we should ALWAYS use the previous attribute
		//Extra 3: Try using the 'rule of five' as it is. Try the "zero trust" ideology and implement constructors and "operator=" ONLY WHEN NEEDED 

		class DiTestClass
		{
		public :
			DiTestClass() = delete;

			//Rule of five : 
			DiTestClass(const DiTestClass & other) = delete;
			DiTestClass& operator = (const DiTestClass & other) = delete;
			DiTestClass(const DiTestClass && other) = delete;
			DiTestClass& operator = (const DiTestClass && other) = delete;
			~DiTestClass() = delete;
			//virtual ~DiTestClass() = delete;

			template<typename T>
			static T add(T first, T second);
			void say(std::string_view message) const;
			

			std::string_view getMemberVariable();
			void setMemberVariable(std::string_view newValue);

		private :
			std::string_view m_memberVariable;
		};

		

	}
}
#endif
