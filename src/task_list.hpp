#ifndef DRUDGERY_TASK_LIST
#define DRUDGERY_TASK_LIST

#include <string>
#include "task.hpp"
#include <vector>

class task_list
{
	public:
		void add(const task& item);
		void remove(const unsigned int index);

		unsigned int size() const;

		task& operator[](const unsigned int index);
		const task operator[](const unsigned int index) const;

		bool save(const std::string& filename) const;
		bool load(const std::string& filename);

		bool operator==(const task_list& rhs) const;
		bool operator!=(const task_list& rhs) const;

	private:
		std::vector<task> list_;
};

#endif