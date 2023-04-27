package main

import(
	"fmt"
	"sync"
	"os"
)

var (
	w sync.WaitGroup
	lock1 = 0
	lock2 = 0
	count = 0
	ch1 = make (chan int)
	ch2 = make (chan int)
	ch3 = make (chan int)
	ch4 = make (chan int)
	ch5 = make (chan int)
)

func routineA(){
	for{
		<-ch1
		fmt.Printf("A")
		if(lock1 == 0){
			lock1++
			ch2<-1
		}else if lock1 == 1{
			lock1++
			ch1<-1
		}else{
			lock1=0
			ch3<-1
		}
	}
}


func routineB(){
	for{
		<-ch1
		fmt.Printf("B")
		if(lock1 == 0){
			lock1++
			ch2<-1
		}else if lock1 == 1{
			lock1++
			ch1<-1
		}else{
			lock1=0
			ch3<-1
		}
	}
}

//revisar C
func routineC(){
	for{
		<-ch2
		fmt.Printf("C")
		ch4<-1
		/*if(lock2==0){
			lock2++
			ch4<-4
		}else{
			lock2=0
			ch4<-1
		}*/
	}
}


func routineD(){
	for{
		<-ch3
		fmt.Printf("D")
		ch4<-1
	}
}


func routineE(){
	for{
		<-ch4
		fmt.Printf("E")
		
		//ch2<-1
		//ch4<-1
		count++
		if count == 20 {
			fmt.Printf("\n")
			os.Exit(1)
		}
		if lock1 == 0 {
			fmt.Printf("\n");
		}
		ch1<-1
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

/*func manageSignals(){
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
}*/

func main(){
	go routineE()
	go routineD()
	go routineC()
	go routineB()
	go routineA()
	ch1<-1
	var input string
	fmt.Scanln(&input)
}