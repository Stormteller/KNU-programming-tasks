package main

import ("fmt"
	"sync"
	"math/rand"
	"time"
)

var middleMutex = &sync.Mutex{}

func getRandElem() [2]int {
	var arrAns [2]int
	arrAns[0] = rand.Intn(3)
	var shift = rand.Intn(2)
	if shift == 1 {
		arrAns[1] = (arrAns[0] + 1) % 3
	} else {
		arrAns[1] = (arrAns[0] + 2) % 3
	}
	return arrAns
}

func in(arr [2]int, elem int) bool {
	if arr[0] == elem || arr[1] == elem {
		return true
	}
	return false
}

func tobaccoGuy(elemChan chan [2]int, restartChan chan bool)  {
	for {
		var components = <- elemChan
		middleMutex.Lock()
		if in(components, 0) && in(components, 1) {
			fmt.Println("Taken by tobacco guy")
			time.Sleep(500 * time.Millisecond)
			fmt.Println("Releazed by tobacco guy")
			restartChan <- true
		} else {
			elemChan <- components
		}
		middleMutex.Unlock()
	}
}

func paperGuy(elemChan chan [2]int, restartChan chan bool) {
	for {
		var components = <- elemChan
		middleMutex.Lock()
		if in(components, 1) && in(components, 2) {
			fmt.Println("Taken by paper guy")
			time.Sleep(500 * time.Millisecond)
			fmt.Println("Releazed by paper guy")
			restartChan <- true
		} else {
			elemChan <- components
		}
		middleMutex.Unlock()
	}
}

func matchGuy(elemChan chan [2]int, restartChan chan bool) {
	for {
		var components = <- elemChan
		middleMutex.Lock()
		if in(components, 0) && in(components, 2) {
			//middleMutex.Lock()
			fmt.Println("Taken by match guy")
			time.Sleep(500 * time.Millisecond)
			fmt.Println("Releazed by match guy")
			restartChan <- true
		} else {
			elemChan <- components
		}
		middleMutex.Unlock()
	}
}

func main() {
	var restartChan = make(chan bool)
	var elemChan = make(chan [2]int)
	go tobaccoGuy(elemChan, restartChan)
	go paperGuy(elemChan, restartChan)
	go matchGuy(elemChan, restartChan)
	for {
		elemChan <- getRandElem()
		<- restartChan
	}
}
