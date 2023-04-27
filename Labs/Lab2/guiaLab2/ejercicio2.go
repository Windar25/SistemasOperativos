package main

import (
"fmt"
"sync"
)

var (
	buffer      [5]int = [5]int{-1, -1, -1, -1, -1}
	index       int
	wg          sync.WaitGroup
	lock1       sync.Mutex
	lock2		sync.Mutex
	ch1         = make(chan int, 1)
	ch2         = make(chan int, 1)
	empty = 5	//cuenta el número de slots vacíos
	full = 0	//cuenta el número de slots llenos
	mutex = 1
)

func down(value int){
	var lock sync.Mutex
	lock.Lock()
	if value > 0 {
		value --
	}else if value == 0{
		<-ch1
	}
	lock.Unlock()
}

func up(value int){
	var lock sync.Mutex
	lock.Lock()
	value ++
	if cap(ch1) == 0 {
		ch1<-1
		value--
	}
	lock.Unlock()
}

// Si el productor llena el buffer, debe bloquearse hasta que el consumidor consuma algo
func productor() {
	for n := 0; n < 20; n++ {
		item := n * n 	
		down(empty)
		down(mutex)
		index = n%5
		buffer[index] = item
		fmt.Printf("productor %d %d %v\n", index, item, buffer)
		up(mutex)
		up(full)
	}
	wg.Done()
}

// Casos a considerar:
// Si el consumidor no tiene espacios donde consumir, debe detenerse


func consumidor() {
	var item int
	for n := 0; n < 20; n++ {
		down(full)
		down(mutex)
		index = n % 5
		item = buffer[index]
		buffer[index] = -1
		index--
		up(mutex)
		up(empty)
		fmt.Printf("consumidor %d %d %v\n", index, item, buffer)
	}
	wg.Done()
}

func main() {
	wg.Add(2)
	go consumidor()
	go productor()
	wg.Wait()
  }	
