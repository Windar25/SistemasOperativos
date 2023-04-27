package main

import(
	"fmt"
	"sync"
	"os"
)

var (
	w sync.WaitGroup
	count = 0
	ch1 = make (chan int, 1)
	ch2 = make (chan int, 1)
	ch3 = make (chan int, 1)
	ch4 = make (chan int, 1)
	ch5 = make (chan int, 1)
	ch6 = make (chan int, 1)
	ch7 = make (chan int, 1)
	ch8 = make (chan int, 1)
)

func routineA(){
	for{
		ch1<-1
		fmt.Printf("A")
		<-ch2
	}
}


func routineB(){
	for{
		ch1<-1
		fmt.Printf("B")
		<-ch2
	}
}


func routineC(){
	for{
		<-ch5
		fmt.Printf("C")
		ch6<-1
	}
}


func routineD(){
	for{
		<-ch6
		fmt.Printf("D")
		ch7<-1
	}
}


func routineE(){
	for{
		<-ch7
		fmt.Printf("E")
		ch8<-1
		//ch2<-1
		//ch4<-1
		count++
	}
}

/*func manageSelects(){
	select{
		case <-ch3: 
			ch4<-1
		case <-ch1: 
			ch2<-1
		default:
			manageSelects()
	}
	ch5<-1
	<-ch8
	count ++
	if count == 50 {
		os.Exit(1)
	}
}*/

func manageSignals(){
	for{
		select{
		case <-ch3: 
			ch4<-1
			ch5<-1
			<-ch8
		case <-ch1: 
			ch2<-1
			ch5<-1
			<-ch8
	}
	
	count ++
		if count == 50 {
			os.Exit(1)
		}
	}	
}

func main(){
	go routineE()
	go routineD()
	go routineC()
	go routineB()
	go routineA()
	manageSignals()
	fmt.Printf("\n")
}