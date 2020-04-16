#include "pintos_thread.h"

struct station
{
	struct lock *lock;
	struct condition *notfull; //是否还有空位
	struct condition *full;	   //是否所有的座位都有人坐了

	int waiting_passenger;	//正在等待的乘客的人数
	int boarding_passenger; //正在登机的乘客的人数

	int seat;//某趟列车的座位数目
};

void station_init(struct station *station)
{
	station->lock = malloc(sizeof(struct lock));
	station->notfull = malloc(sizeof(struct condition));
	station->full = malloc(sizeof(struct condition));

	lock_init(station->lock);
	cond_init(station->notfull);
	cond_init(station->full);

	station->boarding_passenger = 0;
	station->waiting_passenger = 0;

	station->seat = 0;
}

void station_load_train(struct station *station, int count)
{
	lock_acquire(station->lock);
	station->seat = count;
	while ((station->waiting_passenger > 0 && station->seat > 0) || station->boarding_passenger > 0)
	{
		cond_broadcast(station->notfull,station->lock);
		cond_wait(station->full,station->lock);
	}
	station->seat = 0;
	lock_release(station->lock);
	
}

void station_wait_for_train(struct station *station)
{
	lock_acquire(station->lock);
	station->waiting_passenger += 1;
	while (station->seat == 0)
		cond_wait(station->notfull,station->lock);

	station->boarding_passenger += 1;
	station->waiting_passenger -= 1;
	station->seat -= 1;

	lock_release(station->lock);
}

void station_on_board(struct station *station)
{
	lock_acquire(station->lock);
	station->boarding_passenger -= 1;

	if((station->seat == 0 || station->waiting_passenger == 0) && station->boarding_passenger == 0)
		cond_signal(station->full,station->lock);
	lock_release(station->lock);
}
