#ifndef UNCOPYABLE_H_
#define UNCOPYABLE_H_ 1

namespace Uncopyable_ 
{
	/// Private copy ctor and copy assignment ensures derived classes
	/// cannot be copied
	class Uncopyable
	{
	protected:
		Uncopyable() { }
		virtual ~Uncopyable() { }

	private: // Make private to prevent copying
		Uncopyable( const Uncopyable& );
		const Uncopyable& operator=( const Uncopyable& );
	}; // End class Uncopyable
}; // End namespace Uncopyable_

typedef Uncopyable_::Uncopyable uncopyable;

#endif // UNCOPYABLE_H_


