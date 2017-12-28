package main

import (
	"fmt"
	"sync"
	"math/rand"
	"time"
)

const N = 100
var seed = rand.NewSource(time.Now().UnixNano());
var random = rand.New(seed)

func task(soldiers []int, from int, to int, wg *sync.WaitGroup, finish chan bool, again chan bool) {
	var nextRow = make([]int, N)
	for {
		for i := from; i < to; i++ {
			if i == 0 {
				if soldiers[i] == soldiers[i+1] {
					nextRow[i] = soldiers[i]
				} else {
					nextRow[i] = 0
				}
			} else if i == len(soldiers) - 1 {
				if soldiers[i] == soldiers[i-1] {
					nextRow[i] = soldiers[i]
				} else {
					nextRow[i] = 1
				}

			} else {
				var prev = soldiers[i-1]
				var now = soldiers[i]
				var next = soldiers[i+1]

				if prev > now || now > next {
					nextRow[i] = (now + 1) % 2
				} else {
					nextRow[i] = now
				}
			}
		}
		wg.Done()
		select{
		case <-finish:
			return
		case <-again:
		}
		for i := from; i < to; i++ {
			soldiers[i] = nextRow[i]
		}

	}
}

func checker(soldiers []int, wg *sync.WaitGroup, finish chan bool, again chan bool) {
	for {
		wg.Wait()
		var done = true
		for i:=0; i < len(soldiers)-1 && done; i++ {
			if soldiers[i] > soldiers[i+1] {
				done = false
			}
		}
		fmt.Println(soldiers)
		if done {
			fmt.Println("DONE")
			finish <- true
			finish <- true
			return
		} else {
			wg.Add(2)
			again <- true
			again <- true
		}
	}
}

func main() {
	var soldiers = make([]int, N)
	var finish = make(chan bool)
	var again = make(chan bool)
	var wg = &sync.WaitGroup{}
	wg.Add(2)
	for i := 0; i < N; i++ {
		soldiers[i] = random.Intn(2)
	}

	fmt.Println(soldiers)
	go task(soldiers, 0, N/2, wg, finish, again)
	go task(soldiers, N/2, N, wg, finish, again)
	checker(soldiers, wg, finish, again)

}
