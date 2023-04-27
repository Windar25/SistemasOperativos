package main

import(
	"fmt"
	"os"
)

var (
	ch1 = make (chan int, 1)
	ch2 = make (chan int, 1)
	ch3 = make (chan int, 1)
	ch4 = make (chan int, 1)
	ch5 = make (chan int, 1)
	ch6 = make (chan int, 1)
	ch7 = make (chan int, 1)
	llave = 0
	count = 0
)

func routineA(){
	//defer 	w.Done()
	for{
		fmt.Printf("A")
		llave = 0
		ch1<-1
		count++
		if count == 10 {
			os.Exit(1)
		}
		<-ch5
	}

}

//ACDEBCDE
func routineB(){
	//defer 	w.Done()
	for{
		<-ch4
		fmt.Printf("B")
		llave = 1
		ch1<-1
	}
}

// A -> activas 1
// CDE > activas 2
// B -> activas 3
//	CDE > activas 4

func routineC(){
	//defer 	w.Done()
	for{
		<-ch1
		fmt.Printf("C")
		ch2<-1
	}
}


func routineD(){
	//defer 	w.Done()
	for{
		<-ch2
		fmt.Printf("D")
		ch3<-1
	}

}


func routineE(){
	//defer 	w.Done()
	for{
		<-ch3
		fmt.Printf("E")
		if llave == 0{
			ch4<-1
		}else{
			ch5<-1
		}
	}
}
//primero se imprime A
//luego se imprime CDE
//luego B
//luego CDE

func main(){
	go routineA()
	go routineB()
	go routineC()
	go routineD()
	go routineE()
	var input string
	fmt.Scanln(&input)
}