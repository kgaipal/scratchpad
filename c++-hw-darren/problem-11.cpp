/**
11. Implement a Singleton.  It's the most over used and mis-used
design pattern.  Everyone knows the "textbook" implementation of the
singleton but think of all the different ways you can implement it and
what are their pros/cons?  Make a thread-safe version.

Sol:
I have attempted two patterns, both thread safe and accepting no arguments to forward to
class they are instantiating which is the most obvious disadvantage of this approach. Best
way to have a single instance living is to have a shared_ptr on the instance not the class
itself and let it change 'state' over the time.

Disadvantage with the singleton class is when each client code would instantiate this
class/object with different 'state'. This is possible when makeInstance() below accepts
some arguments to forward to the actual class instance while constructing first time. If
no arguments and each client code is okay with same initial default 'state' of instance
then this pattern might be fine.

Best is to avoid use of a Singleton pattern and redesign class usage heirarchies.

*/

// first implementation (book-ish way): one static public function giving the only
// instance of singleton class. MutexLocker class is at the end of this file.
class Singelton
{
public:
	static Singleton* makeInstance()
	{
		MutexLocker ml(&staticMutex);
		if (instance == nullptr) {
			instance = new Singleton();
		}
		return instance;
		// class lock release when scope ends
	}

	~Singleton() { }

	void someFunction()
	{
		MutexLocker ml(&m_mutex);

		// ... some code

		// member lock released when we this scope ends
	}

protected:
	// Need a object level mutex because makeInstance() and object functions can be
	// accessed by different thread(s) at any time. Having two mutexes makes no
	// contention for the threads needing the only instance of 'this' and between
	// those who want to work on 'this'.
	pthread_mutex_t m_mutex;

private:
	Singleton() { }

	// copies are not allowed because this is thread safe and we cannot have
	// 'staticMutex' copied into multiple instances of Singleton_2 itself.
	Singleton(const Singleton&) { }
	Singleton& operator=() { return *this; }

	static Singleton* instance;
	static pthread_mutex_t staticMutex;
};

Singleton* Singleton::instance = nullptr;

// Second implementation: This is very similar to a shared pointer to a class. We will
// create the object we would like to manage and record that a new instance is created by
// incrementing the count for each call of makeInstance() and decrement for each
// deleteInstance(). Once the count reaches 0 we delete the object that time very similar
// to shared_ptr. We increase reference count in ctor, copy ctor and = operator and
// decrease count in dtor and delete istance once it reaches zero.
//
// One disadvantage with this approach however is that the instance which once goes to 0
// after multiple deletions, it can come back to life again when next dtor is called. To
// avoid that we avoid deleting instance completely even when count reaches 0.
template<typename T>
class Singleton_2
{
public:
	Singleton_2()
	{
		MutexLocker ml(&staticMutex);
		increaseCount();
		return instance;
	}

	Singleton_2(const Singleton_2&/*dont care bcoz members are static*/)
	{
		MutexLocker ml(&staticMutex);
		increaseCount();
		return instance;
	}

	Singleton_2& operator=(Singleton_2&/*dont care bcoz members are static*/)
	{
		MutexLocker ml(&staticMutex);
		increaseCount();
		return *this;
	}

	~Singleton_2()
	{
		MutexLocker ml(&staticMutex);
		decreaseCount();
	}

	// T::func() can be called: Singleton_2 s;
	// ... s->func();
	// ... (*s)->func(); or (**s).func();
	// ... s.get()->func();
	T* operator->() const { return instance; } // access to T*
	T& operator*() const { return *instance; } // derefernce T
	T* get() const { return instance; }	   // access to T*

private:
	static void increaseCount()
	{
		if (instance == nullptr) {
			instance = new T();
		}

		instancesCount++;
	}

	static void decreaseCount()
	{
		instancesCount--; // decrease the references to this item

		// if nobody references this instance now, delete it
		if (instancesCount == 0) {

			// Note: This can be dangerous because we dont want 'instance' to
			// come back to life again after count has reached 0 when some
			// client code again call ctor. This then will an instance in some
			// different 'state'. We can altogether avoid this counter concept
			// and never delete this object unless program dies or some
			// specific function in this class which will delete it. Leaving
			// this as it is for now.
			if (instance != nullptr) {
				delete instance;
				instance = nullptr;
			}
		}
	}

	static pthread_mutex_t staticMutex;
	static T* instance;
	static unsigned int instancesCount;
};

template<typename T>
unsigned int Singleton_2<T>::instancesCount = 0;

// All pthread functions are contention free for threads as we are not maintaining state of member variable.
class MutexLocker
{
public:
	MutexLocker(pthread_mutex_t* mutex, int timeout_ms = -1)
		: m_mutex(nullptr)
	{
		if (pthread_mutex_lock(m_mutex) == EOK) {
			// class 'state' will change only when a thread locks it!
			// other threads wait on 'if (...)' above (outside this if block)
			m_mutex = mutex;
		}
	}

	~MutexLocker()
	{
		if (m_mutex != nullptr) {
			pthread_mutex_unlock(m_mutex);

			// ...
			// no other class 'state' modifying statement follow after
			// unlocking mutex, not thread safe if we do
		}
	}

	inline bool locked() const { return m_mutex != nullptr; }

private:
	pthread_mutex_t *m_mutex; // a valid value only when we actually lock on the mutex
};
