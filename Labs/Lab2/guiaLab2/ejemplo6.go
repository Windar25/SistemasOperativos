package main

import(
	"fmt"
	"sync"
)
//seccion critica
//Si count = 1
//P1:				P2:
//reg = count = 1	
//					reg = count =1
// reg++			
// 					reg++
// count = reg = 2
//					count = reg = 2
// se esperaba 3 y llegaron solo 2

func worker(){
	for x:=0; x<1000000; x++{
		count ++;
		fmt.Println(count)
	}
	wg.Done()
}

var (
	count int
	wg sync.WaitGroup
)

func main(){
	for x:=0; x<5 ; x++{
		wg.Add(1)
		go worker()
	}
	wg.Wait()
	fmt.Printf("El valor esperado del count es 5000000 y el valor final es %d\n",count)
}