package main

import ("fmt"
	"math/rand"
	"time"
	"sync"
)

const N = 1000
var storage [N]int
var w sync.WaitGroup

func ivanovProducer(bufferChan chan int, done chan bool) {
	defer w.Done()
	for i := 0; i < N; i++ {
		bufferChan <- storage[i]
		time.Sleep(10 * time.Millisecond)
		fmt.Println("Stolen ", storage[i])
	}
	done <- true
}

func petrovBuffer(inChan <- chan int, outChan chan int, doneIn <- chan bool, doneOut chan bool) {
	defer w.Done()
	for {
		select {
		case s := <- inChan: outChan <- s
		case <- doneIn:
			doneOut <- true; return
		}
	}
}

func necheporukConsumer (inChan <- chan int, done <- chan bool) {
	defer w.Done()
	sum := 0
	for {
		select {
		case s:= <- inChan: sum += s
		case <- done:
			fmt.Println(sum); return
		}
	}
}

func main() {
	doneProd := make(chan bool)
	doneCons := make(chan bool)
	w.Add(3)
	prodBuffChan := make(chan int)
	buffConsChan := make(chan int, 100)
	for i := 0; i < N; i++ {
		storage[i] = rand.Intn(10)
	}

	go ivanovProducer(prodBuffChan, doneProd)
	go petrovBuffer(prodBuffChan, buffConsChan, doneProd, doneCons)
	go necheporukConsumer(buffConsChan, doneCons)
	w.Wait()
}
