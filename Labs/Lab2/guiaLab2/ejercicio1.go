package main

import(
	"fmt"
	"sync"
)

var (
	wg sync.WaitGroup
	ch1 = make(chan int,1)
	ch2 = make(chan int,1)
	ch3	= make(chan int,1)
)

func worker1(){
	<-ch1
	fmt.Printf("Sistemas ")
	wg.Done()
	ch2<-1
}

func worker2(){
	fmt.Printf("INF239 ")
	wg.Done()
	ch1<-1

}

func worker3(){
	<-ch2
	fmt.Printf("Operativos ")
	wg.Done()
	ch3<-1
}

func worker4(){
	<-ch3
	fmt.Printf("\n")
	wg.Done()
}

func main(){
	wg.Add(4)
	go worker1()
	go worker2()
	go worker3()
	go worker4()
	wg.Wait()
}