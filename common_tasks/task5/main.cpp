#include "Time.h"

void do_work() {
	Time t;
	t.SetHours(1);
	Time t2 = t;
	t2.SetHours(2);
	t2.PrintTime();
	{
		t2.SetHours(12);
		t2.PrintTime();
		Time t2(22, 22, 22);
		t2.PrintTime();
	}
	t2.PrintTime();
	Time t3(3, 3, 3);
	t3 = t;
	t3.SetHours(3);
	t3.PrintTime();
}

int main() {
	do_work();
}
