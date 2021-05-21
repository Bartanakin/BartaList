#include"main.h"

bool print(int i) {
	std::cout << i << " ";
	return true;
}

int main() {
	BartaList<int> list1(_BARTA_SORTING_PREDICATE_FIRST(int));
	std::shared_ptr<int> a = std::make_shared<int>(2);
	list1.addWeakToList(a);
	{
		std::shared_ptr<int> b = std::make_shared<int>(3);
		list1.addWeakToList(b);

		list1.forEach(print); std::cout << std::endl;
	}
	list1.addSharedToList(5);
	list1.forEach(print); std::cout << std::endl;
	list1.remove(list1.findData(4));
	list1.forEach(print); std::cout << std::endl;
	list1.clear();
	return 0;
}