# Philosophers

#### # 과제 설명

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

`./philo number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat] ` 을 사용해 실행한다. (단, 마지막 인자는 반드시 먹어야하는 횟수로 입력하지않으면 1번씩 먹는 것으로 실행)

출력문구는 아래와 같이 출력함

- `timestamp_in_ms X has taken a fork` : 철학자가 포크를 집었을때

- `timestamp_in_ms X is eating` : 철학자가 식사 중일때

- `timestamp_in_ms X is sleeping` : 철학자가 잠을 자는 중일때

- `timestamp_in_ms X is thinking` : 철학자가 생각 중일때

- `timestamp_in_ms X died` : 철학자가 죽음
- `Must eat count reached` : 철학자가 죽지않았지만 마지막 인자인 반드시 먹어야하는 횟수를 만족하여 종료될 때

`X` : 철학자의 번호tex;	/* 문구 출력 중 */

