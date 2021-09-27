# Philosophers

##### **식사하는 철학자**

###### 1. 조건

 - 철학자는 2명 이상이다.
 - 철학자는 정해진 시간 안에 먹지 않으면 죽는다.
 - 철학자 한 명이 죽으면 프로그램을 종료한다.
 - 철학자는 먹기위해 포크 2개를 잡아야한다.
 - 철학자는 먹고 - 자고 - 생각하는 것을 반복한다.
 - 실행인자는 5개 혹은 6개 이다.

![philo](https://upload.wikimedia.org/wikipedia/commons/7/7b/An_illustration_of_the_dining_philosophers_problem.png)

- [사진 출처 : wiki](https://upload.wikimedia.org/wikipedia/commons/7/7bAn_illustration_of_the_dining_philosophers_problem.png)



###### 2. 실행

`./ philo number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat] `

◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died

