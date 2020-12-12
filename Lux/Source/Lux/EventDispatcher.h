#pragma once

#include "lxpch.h"
#include "Lux/Core.h"

namespace Lux
{
	template<typename... Args>
	class EventDispatcher
	{
		EventDispatcher() = delete;
		EventDispatcher(const EventDispatcher&) = delete;
		EventDispatcher(EventDispatcher&&) = delete;
	};

	template<>
	class EventDispatcher<>
	{
	private:
		using EventFn = std::function<void()>;
		std::vector <EventFn> m_Binds;
	public:
		void Bind(EventFn fn)
		{
			m_Binds.push_back(fn);
		}

		template<typename T>
		void Bind(void(T::*fn)(), T* object)
		{
			m_Binds.push_back(std::bind(std::function<void(T*)>(fn), object));
		}

		void Unbind(EventFn fn)
		{
			using FnType = void(*)();
			for (std::vector<EventFn>::iterator it = m_Binds.begin(); it != m_Binds.end();)
			{
				if (*it->target<FnType>() == *fn.target<FnType>())
					it = m_Binds.erase(it);
				else
					it++;
			}
		}

		void UnbindAll()
		{
			m_Binds.clear();
		}

		void Dispatch()
		{
			for (auto fn : m_Binds)
				fn();
		}
	};

	template<typename P1>
	class EventDispatcher<P1>
	{
	private:
		using EventFn = std::function<void(P1)>;
		std::vector <EventFn> m_Binds;
	public:
		void Bind(EventFn fn)
		{
			m_Binds.push_back(fn);
		}

		template<typename T>
		void Bind(void(T::* fn)(P1), T* object)
		{
			m_Binds.push_back(std::bind(std::function<void(T*, P1)>(fn), object,
				std::placeholders::_1));
		}

		void Unbind(EventFn fn)
		{
			using FnType = void(*)(P1);
			for (std::vector<EventFn>::iterator it = m_Binds.begin(); it != m_Binds.end();)
			{
				if (*it->target<FnType>() == *fn.target<FnType>())
					it = m_Binds.erase(it);
				else
					it++;
			}
		}

		void UnbindAll()
		{
			m_Binds.clear();
		}

		void Dispatch(P1 p1)
		{
			for (auto fn : m_Binds)
				fn(p1);
		}
	};

	template<typename P1, typename P2>
	class EventDispatcher<P1, P2>
	{
	private:
		using EventFn = std::function<void(P1, P2)>;
		std::vector <EventFn> m_Binds;
	public:
		void Bind(EventFn fn)
		{
			m_Binds.push_back(fn);
		}

		template<typename T>
		void Bind(void(T::* fn)(P1, P2), T* object)
		{
			m_Binds.push_back(std::bind(std::function<void(T*, P1, P2)>(fn), object,
				std::placeholders::_1, std::placeholders::_2));
		}

		void Unbind(EventFn fn)
		{
			using FnType = void(*)(P1, P2);
			for (std::vector<EventFn>::iterator it = m_Binds.begin(); it != m_Binds.end();)
			{
				if (*it->target<FnType>() == *fn.target<FnType>())
					it = m_Binds.erase(it);
				else
					it++;
			}
		}

		void UnbindAll()
		{
			m_Binds.clear();
		}

		void Dispatch(P1 p1, P2 p2)
		{
			for (auto fn : m_Binds)
				fn(p1, p2);
		}
	};

	template<typename P1, typename P2, typename P3>
	class EventDispatcher<P1, P2, P3>
	{
	private:
		using EventFn = std::function<void(P1, P2, P3)>;
		std::vector <EventFn> m_Binds;
	public:
		void Bind(EventFn fn)
		{
			m_Binds.push_back(fn);
		}

		template<typename T>
		void Bind(void(T::* fn)(P1, P2, P3), T* object)
		{
			m_Binds.push_back(std::bind(std::function<void(T*, P1, P2, P3)>(fn), object,
				std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}

		void Unbind(EventFn fn)
		{
			using FnType = void(*)(P1, P2, P3);
			for (std::vector<EventFn>::iterator it = m_Binds.begin(); it != m_Binds.end();)
			{
				if (*it->target<FnType>() == *fn.target<FnType>())
					it = m_Binds.erase(it);
				else
					it++;
			}
		}

		void UnbindAll()
		{
			m_Binds.clear();
		}

		void Dispatch(P1 p1, P2 p2, P3 p3)
		{
			for (auto fn : m_Binds)
				fn(p1, p2, p3);
		}
	};

	template<typename P1, typename P2, typename P3, typename P4>
	class EventDispatcher<P1, P2, P3, P4>
	{
	private:
		using EventFn = std::function<void(P1, P2, P3, P4)>;
		std::vector <EventFn> m_Binds;
	public:
		void Bind(EventFn fn)
		{
			m_Binds.push_back(fn);
		}

		template<typename T>
		void Bind(void(T::* fn)(P1, P2, P3, P4), T* object)
		{
			m_Binds.push_back(std::bind(std::function<void(T*, P1, P2, P3, P4)>(fn), object,
				std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		}

		void Unbind(EventFn fn)
		{
			using FnType = void(*)(P1, P2, P3, P4);
			for (std::vector<EventFn>::iterator it = m_Binds.begin(); it != m_Binds.end();)
			{
				if (*it->target<FnType>() == *fn.target<FnType>())
					it = m_Binds.erase(it);
				else
					it++;
			}
		}

		void UnbindAll()
		{
			m_Binds.clear();
		}

		void Dispatch(P1 p1, P2 p2, P3 p3, P4 p4)
		{
			for (auto fn : m_Binds)
				fn(p1, p2, p3, p4);
		}
	};

	template<typename P1, typename P2, typename P3, typename P4, typename P5>
	class EventDispatcher<P1, P2, P3, P4, P5>
	{
	private:
		using EventFn = std::function<void(P1, P2, P3, P4, P5)>;
		std::vector <EventFn> m_Binds;
	public:
		void Bind(EventFn fn)
		{
			m_Binds.push_back(fn);
		}

		template<typename T>
		void Bind(void(T::* fn)(P1, P2, P3, P4, P5), T* object)
		{
			m_Binds.push_back(std::bind(std::function<void(T*, P1, P2, P3, P4, P5)>(fn), object,
				std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
		}

		void Unbind(EventFn fn)
		{
			using FnType = void(*)(P1, P2, P3, P4, P5);
			for (std::vector<EventFn>::iterator it = m_Binds.begin(); it != m_Binds.end();)
			{
				if (*it->target<FnType>() == *fn.target<FnType>())
					it = m_Binds.erase(it);
				else
					it++;
			}
		}

		void UnbindAll()
		{
			m_Binds.clear();
		}

		void Dispatch(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
		{
			for (auto fn : m_Binds)
				fn(p1, p2, p3, p4, p5);
		}
	};

	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	class EventDispatcher<P1, P2, P3, P4, P5, P6>
	{
	private:
		using EventFn = std::function<void(P1, P2, P3, P4, P5, P6)>;
		std::vector <EventFn> m_Binds;
	public:
		void Bind(EventFn fn)
		{
			m_Binds.push_back(fn);
		}

		template<typename T>
		void Bind(void(T::* fn)(P1, P2, P3, P4, P5, P6), T* object)
		{
			m_Binds.push_back(std::bind(std::function<void(T*, P1, P2, P3, P4, P5, P6)>(fn), object,
				std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5,
				std::placeholders::_6));
		}

		void Unbind(EventFn fn)
		{
			using FnType = void(*)(P1, P2, P3, P4, P5, P6);
			for (std::vector<EventFn>::iterator it = m_Binds.begin(); it != m_Binds.end();)
			{
				if (*it->target<FnType>() == *fn.target<FnType>())
					it = m_Binds.erase(it);
				else
					it++;
			}
		}

		void UnbindAll()
		{
			m_Binds.clear();
		}

		void Dispatch(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
		{
			for (auto fn : m_Binds)
				fn(p1, p2, p3, p4, p5, p6);
		}
	};

	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	class EventDispatcher<P1, P2, P3, P4, P5, P6, P7>
	{
	private:
		using EventFn = std::function<void(P1, P2, P3, P4, P5, P6, P7)>;
		std::vector <EventFn> m_Binds;
	public:
		void Bind(EventFn fn)
		{
			m_Binds.push_back(fn);
		}

		template<typename T>
		void Bind(void(T::* fn)(P1, P2, P3, P4, P5, P6, P7), T* object)
		{
			m_Binds.push_back(std::bind(std::function<void(T*, P1, P2, P3, P4, P5, P6, P7)>(fn), object,
				std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5,
				std::placeholders::_6, std::placeholders::_7));
		}

		void Unbind(EventFn fn)
		{
			using FnType = void(*)(P1, P2, P3, P4, P5, P6, P7);
			for (std::vector<EventFn>::iterator it = m_Binds.begin(); it != m_Binds.end();)
			{
				if (*it->target<FnType>() == *fn.target<FnType>())
					it = m_Binds.erase(it);
				else
					it++;
			}
		}

		void UnbindAll()
		{
			m_Binds.clear();
		}

		void Dispatch(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
		{
			for (auto fn : m_Binds)
				fn(p1, p2, p3, p4, p5, p6, p7);
		}
	};

	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	class EventDispatcher<P1, P2, P3, P4, P5, P6, P7, P8>
	{
	private:
		using EventFn = std::function<void(P1, P2, P3, P4, P5, P6, P7, P8)>;
		std::vector <EventFn> m_Binds;
	public:
		void Bind(EventFn fn)
		{
			m_Binds.push_back(fn);
		}

		template<typename T>
		void Bind(void(T::* fn)(P1, P2, P3, P4, P5, P6, P7, P8), T* object)
		{
			m_Binds.push_back(std::bind(std::function<void(T*, P1, P2, P3, P4, P5, P6, P7, P8)>(fn), object,
				std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5,
				std::placeholders::_6, std::placeholders::_7, std::placeholders::_8));
		}

		void Unbind(EventFn fn)
		{
			using FnType = void(*)(P1, P2, P3, P4, P5, P6, P7, P8);
			for (std::vector<EventFn>::iterator it = m_Binds.begin(); it != m_Binds.end();)
			{
				if (*it->target<FnType>() == *fn.target<FnType>())
					it = m_Binds.erase(it);
				else
					it++;
			}
		}

		void UnbindAll()
		{
			m_Binds.clear();
		}

		void Dispatch(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
		{
			for (auto fn : m_Binds)
				fn(p1, p2, p3, p4, p5, p6, p7, p8);
		}
	};

	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	class EventDispatcher<P1, P2, P3, P4, P5, P6, P7, P8, P9>
	{
	private:
		using EventFn = std::function<void(P1, P2, P3, P4, P5, P6, P7, P8, P9)>;
		std::vector <EventFn> m_Binds;
	public:
		void Bind(EventFn fn)
		{
			m_Binds.push_back(fn);
		}

		template<typename T>
		void Bind(void(T::* fn)(P1, P2, P3, P4, P5, P6, P7, P8, P9), T* object)
		{
			m_Binds.push_back(std::bind(std::function<void(T*, P1, P2, P3, P4, P5, P6, P7, P8, P9)>(fn), object,
				std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5,
				std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9));
		}

		void Unbind(EventFn fn)
		{
			using FnType = void(*)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
			for (std::vector<EventFn>::iterator it = m_Binds.begin(); it != m_Binds.end();)
			{
				if (*it->target<FnType>() == *fn.target<FnType>())
					it = m_Binds.erase(it);
				else
					it++;
			}
		}

		void UnbindAll()
		{
			m_Binds.clear();
		}

		void Dispatch(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9)
		{
			for (auto fn : m_Binds)
				fn(p1, p2, p3, p4, p5, p6, p7, p8, p9);
		}
	};

	template<typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10>
	class EventDispatcher<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10>
	{
	private:
		using EventFn = std::function<void(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)>;
		std::vector <EventFn> m_Binds;
	public:
		void Bind(EventFn fn)
		{
			m_Binds.push_back(fn);
		}

		template<typename T>
		void Bind(void(T::* fn)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10), T* object)
		{
			m_Binds.push_back(std::bind(std::function<void(T*, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)>(fn), object,
				std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5,
				std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9, std::placeholders::_10));
		}

		void Unbind(EventFn fn)
		{
			using FnType = void(*)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10);
			for (std::vector<EventFn>::iterator it = m_Binds.begin(); it != m_Binds.end();)
			{
				if (*it->target<FnType>() == *fn.target<FnType>())
					it = m_Binds.erase(it);
				else
					it++;
			}
		}

		void UnbindAll()
		{
			m_Binds.clear();
		}

		void Dispatch(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10)
		{
			for (auto fn : m_Binds)
				fn(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
		}
	};

	/* Different implementation of EventDispatcher
	class LUX_API EventDispacher
	{
	public:
		template<typename T>
		using EventFn = std::function<bool(T&)>;

		EventDispacher(Event& event)
			: m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> fn)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = fn(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
	*/

	/*inline std::ostream& operator<<(std::ostream& os, const Event& event)
	{
		return os << event.ToString();
	}*/
}