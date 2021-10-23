## :notebook_with_decorative_cover: ft_containers

#### :page_facing_up: Mandatory part

- Implement the following containers and turn in the necessary files `<container>.hpp`
- You must use std::allocator.
- If the container has an iterator system, you must implement it.
- iterators_traits, reverse_iterator, enable_if, is_integral, equal/lexicographical compare, std::pair, std::make_pair, must be reimplemented.
- For non-member overloads, the keyword friend is allowed. Each use of friend must be justified.
- You must turn in the following containers and their associated functions
  - Vector
  - Map
  - Stack
- Your stack will use your vector class as default underlaying container, it must still be compatible with others containers like the STL one.
- STL containers are forbidden.
- You are allowed to use the STD library.

---

#### 참고자료

- https://www.cplusplus.com/reference/stl/
- https://en.cppreference.com/w/cpp/container
- https://docs.microsoft.com/ko-kr/cpp/standard-library/
- https://gcc.gnu.org/onlinedocs/gcc-4.6.2/libstdc++/api/annotated.html
- https://runebook.dev/ko/docs/cpp/-index-

---

#### 벡터(Vector)

- 데이터 추가가 용이하기 때문에 저장할 데이터가 가변적일 때 사용
- 중간 데이터 삽입이나 삭제는 자원 낭비이므로 일어나지 않아도 되는 경우 사용
- 위치를 알고 있다면 데이터 접근 용이

#### 맵(Map)

- 많은 자료를 정렬해야 할 때 사용
- 많은 자료를 저장하고, 검색이 빨라야 할 때 사용
- 빈번한 삽입과 삭제는 자원 낭비이므로 가급적 사용하지 않음
- 중복 키 불가

---

#### STL(Standard Template Library) 표준 템플릿 라이브러리

- 타입 독립적인 자료구조와 알고리즘을 사용하는 일반화 프로그래밍(Generic programming) 개념을 구현하기 위해 개발되었던 C++ 라이브러리를 지칭하는 말
- 컨테이너, 반복자, 알고리즘으로 구성
- https://namu.wiki/w/%ED%91%9C%EC%A4%80%20%ED%85%9C%ED%94%8C%EB%A6%BF%20%EB%9D%BC%EC%9D%B4%EB%B8%8C%EB%9F%AC%EB%A6%AC

---

#### STD(Standard Library) 표준 라이브러리

- C++ 표준 라이브러리는 여러 제네릭 컨테이너들, 그리고 이러한 컨테이너들과 함수 객체, 제네릭 문자열, 스트림(인터렉티브와 파일 입출력을 포함하는), 몇몇 언어 특징 그리고 숫자의 제곱근을 찾는 것 같은 작업을 위한 모든 함수들을 활용하기 위한 함수들을 제공한다. C++ 표준 라이브러리는 또한 ".h"로 끝나는 ISO C90 C 표준 라이브러리의 18 헤더들을 포함하지만 이것들의 사용은 추천되지 않는다. ".h"로 끝나지 않는 헤더는 C++ 표준 라이브러리에는 존재하지 않는다. C++ 표준 라이브러리의 특징은 std 이름공간 (namespace) 내에 선언된다는 것이다.

  C++ 표준 라이브러리는 표준 템플릿 라이브러리(STL : Standard Template Library)에 의해 도입된 관습에 기반하며, 제네릭 프로그래밍과 STL의 개발자들의 연구에 영향을 받았다. 비록 C++ 표준 라이브러리와 STL이 많은 특징들을 공유하지만, 둘 중 어느것도 다른 하나의 상위 집합은 아니다

- https://ko.wikipedia.org/wiki/C%2B%2B_%ED%91%9C%EC%A4%80_%EB%9D%BC%EC%9D%B4%EB%B8%8C%EB%9F%AC%EB%A6%AC

---

#### Allocator 할당자

- C++의 표준 라이브러리에서 메모리 할당을 관리하는 객체이다. C++표준 라이브러리에서 이용되는 리스트, 셋 등의 다양한 컨테이너 자료구조들은 용도에 따라 동적 메모리 할당을 요구한다. 할당자는 동적 메모리 할당을 통합 관리하는데 필요한 기능이 정의된 객체이다.
- 주요 멤버 함수
  - allocator : 메모리 공간을 할당하여 그 시작 주소를 반환
  - deallocate : 메모리 공간을 해제
  - construct : 할당된 공간에 요소를 저장
  - destroy : 객체 소멸
  - max_size : 할당할 수 있는 최대 크기 반환
- https://en.cppreference.com/w/cpp/memory/allocator
- https://ko.wikipedia.org/wiki/%ED%95%A0%EB%8B%B9%EC%9E%90

---

#### Iterator 반복자

- 반복자(iterator)란 STL 컨테이너에 저장된 요소를 반복적으로 순회하여, 각각의 요소에 대한 접근을 제공하는 객체입니다.
  즉, 컨테이너의 구조나 요소의 타입과는 상관없이 컨테이너에 저장된 데이터를 순회하는 과정을 일반화한 표현입니다.
- 반복자의 종류 (http://tcpschool.com/cpp/cpp_iterator_category)
  - 입력 반복자(input iterator)
  - 출력 반복자(output iterator)
  - 순방향 반복자(forward iterator)
  - 양방향 반복자(bidirectional iterator)
  - 임의 접근 반복자(random access iterator)
- 반복자 카테고리(iterator category)
  - https://narss.tistory.com/entry/%EB%B0%98%EB%B3%B5%EC%9E%90-%EC%B9%B4%ED%85%8C%EA%B3%A0%EB%A6%ACiterator-category
- http://www.soen.kr/lecture/ccpp/cpp4/39-2-6.htm
- https://ansohxxn.github.io/stl/chapter16-2/
- https://en.cppreference.com/w/cpp/iterator

---

#### friend 키워드 - 연산자 오버로딩을 위한

- http://tcpschool.com/cpp/cpp_encapsulation_friend
- https://genesis8.tistory.com/98
- https://thrillfighter.tistory.com/283
- https://choryeonworkshop.tistory.com/130

---

#### enable_if

- https://hellobird.tistory.com/135
- https://modoocode.com/255

---

#### 템플릿 문법

- https://modoocode.com/219
- https://int-i.github.io/cpp/2020-03-11/cpp-template-review/
- https://blog.naver.com/vjhh0712v/221561418596

---

#### new/delete vs allocator

- https://kldp.org/node/109031

---

#### explict

http://opensw.wikidot.com/cpp-fundamentals-explicit

---

#### avl tree

- https://www.hanbit.co.kr/channel/category/category_view.html?cms_code=CMS9990721111
- https://sangwoo-joh.github.io/avl-tree
- https://blog.naver.com/babobigi/220945417209
- https://www.cs.usfca.edu/~galles/visualization/AVLtree.html

---

#### avl tree의 회전

- 각 node마다 height 캐싱
- insert 로직이 실행될 때, height 값을 이용해 balance factor를 계산하여 케이스를 구별하는 작업이 필요
- 아래는 총 4가지 케이스에 따라 회전이 코드로 어떻게 구현되는지 그려 본 것

![avl_jwon (1)](https://user-images.githubusercontent.com/61400214/138542602-8b91b952-6908-4f5b-8916-c06995c7ad49.png)
![avl_jwon (2)](https://user-images.githubusercontent.com/61400214/138542605-187d0a49-0d30-448a-83b4-75b636ae48c7.png)
![avl_jwon (3)](https://user-images.githubusercontent.com/61400214/138542606-90047e23-1a8a-4648-aa99-ae4c24f0f103.png)
![avl_jwon (4)](https://user-images.githubusercontent.com/61400214/138542607-3c187fa6-17a7-4f6c-a91a-7f6c36760f72.png)
![avl_jwon (5)](https://user-images.githubusercontent.com/61400214/138542608-023adc37-7dde-4d08-ab4a-4379fe298c81.png)
![avl_jwon (6)](https://user-images.githubusercontent.com/61400214/138542609-5aefd271-82c4-4759-8990-08b9ce830dfc.png)
![avl_jwon (7)](https://user-images.githubusercontent.com/61400214/138542610-125137fe-d2da-4fbe-90bd-06482b1a881c.png)
![avl_jwon (8)](https://user-images.githubusercontent.com/61400214/138542611-945efccd-36cc-4f2c-8f82-5cdd7395535f.png)
![avl_jwon (9)](https://user-images.githubusercontent.com/61400214/138542612-042302f9-309b-415d-bebe-92a8e3ce9166.png)
![avl_jwon (10)](https://user-images.githubusercontent.com/61400214/138542613-48882b84-f496-4089-90a9-ee10c6cbbe36.png)
![avl_jwon (11)](https://user-images.githubusercontent.com/61400214/138542614-4803c35f-da7a-4b95-9433-b60abb6a17a5.png)
![avl_jwon (12)](https://user-images.githubusercontent.com/61400214/138542615-25210d60-8809-496f-b7e3-d1181262b56c.png)
![avl_jwon (13)](https://user-images.githubusercontent.com/61400214/138542616-43ee9911-33dc-4f9f-b919-407be0fe913f.png)
![avl_jwon (14)](https://user-images.githubusercontent.com/61400214/138542617-8badddb0-aa56-4bdd-acde-21b8ad44d17e.png)
![avl_jwon (15)](https://user-images.githubusercontent.com/61400214/138542618-c7705916-ead4-4095-a806-3c985922ad8e.png)
![avl_jwon (16)](https://user-images.githubusercontent.com/61400214/138542619-b513f85b-d7f9-4c9a-9d01-7fe1cc4b7318.png)
![avl_jwon (17)](https://user-images.githubusercontent.com/61400214/138542620-ae8f9ee3-b058-4fa0-9925-eb7012c079d4.png)
![avl_jwon (18)](https://user-images.githubusercontent.com/61400214/138542621-eeaadea9-8de2-4ebd-8801-baeda48128b3.png)
![avl_jwon (19)](https://user-images.githubusercontent.com/61400214/138542622-e4a86113-79ab-45eb-a91c-8c93eeead906.png)
![avl_jwon (20)](https://user-images.githubusercontent.com/61400214/138542623-3fa66b16-6b4b-411a-a632-8d2fda3cda99.png)
