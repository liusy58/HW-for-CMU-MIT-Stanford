#include "pintos_thread.h"

struct station
{
	struct lock *lock;
	int waiting_passenger;
	int boarding_passenger;

	int seat;
};

void station_init(struct station *station)
{
	station->lock=malloc(sizeof(struct lock));
	lock_init(station->lock);
	station->boarding_passenger=0;
	station->waiting_passenger=0;

	station->seat=0;
}

void station_load_train(struct station *station, int count)
{
	lock_acquire(station->lock);
	station->seat=count;
	while((station->waiting_passenger>0&&station->seat>0)||station->boarding_passenger>0);

	lock_release(station->lock);
	return;
}

void station_wait_for_train(struct station *station)
{
	lock_acquire(station->lock);
	station->waiting_passenger+=1;
	while(station->seat==0);

	station->boarding_passenger+=1;
	station->waiting_passenger-=1;
	station->seat-=1;

	lock_release(station->lock);
}

void station_on_board(struct station *station)
{
	lock_acquire(station->lock);
	station->waiting_passenger-=1;
	lock_release(station->lock);
}
