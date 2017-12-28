package main

import (
	"time"
	"sync"
	"fmt"
	"math/rand"
)

const MAX_PRICE = 100

var seed = rand.NewSource(time.Now().UnixNano());

var random = rand.New(seed);

func pos(slice []int, value int) int {
	for p, v := range slice {
		if v == value {
			return p
		}
	}
	return -1
}

func addPath(graph *[][]int, from int, to int) {
	if from != to {
		var price = rand.Intn(MAX_PRICE)
		(*graph)[from][to] = price + 1
		(*graph)[to][from] = price + 1
		fmt.Printf("From %d to %d path added with price %d\n", from, to, price)
	}
}


func removePath(graph *[][]int, from int, to int) {
	(*graph)[from][to] = 0
	(*graph)[to][from] = 0
	fmt.Printf("From %d to %d path removed\n", from, to)
}

func PathWorker(towns *int, graph *[][]int, rwlock *sync.RWMutex) {
	for {
		rwlock.Lock()
		var randFrom = random.Intn(*towns)
		var randTo = random.Intn(*towns)
		if (*graph)[randFrom][randTo] == 0 && (*graph)[randTo][randFrom] == 0 {
			addPath(graph, randFrom, randTo)
		} else {
			removePath(graph, randFrom, randTo)
		}
		rwlock.Unlock()
		time.Sleep(100 * time.Millisecond)
	}
}

func changePrice(graph *[][]int, from int, to int, price int) {
	if from != to {
		(*graph)[from][to] = price
		(*graph)[to][from] = price
		fmt.Printf("Price %d was set from %d to %d\n", price, from, to)
	}
}

func addTown(towns *int, graph *[][]int) {
	var newLine []int
	*towns++
	for i:=0; i < *towns - 1; i++ {
		(*graph)[i] = append((*graph)[i], 0)
	}
	for i:=0; i < *towns; i++ {
		newLine = append(newLine, 0)
	}
	*graph = append(*graph, newLine)
	if *towns > 1 {
		addPath(graph, *towns-1, random.Intn(*towns - 1))
	}
	fmt.Println("Town added")
}


func removeLastTown(towns *int, graph *[][]int) {
	for i:=0; i < *towns - 1; i++ {
		(*graph)[i] = (*graph)[i][:len((*graph)[i])-1]
	}
	*graph = (*graph)[:len(*graph)-1]
	*towns--
	fmt.Println("Town removed")
}

func TownsWorker(towns *int, graph *[][]int, rwlock *sync.RWMutex) {
	for {
		rwlock.Lock()
		if *towns < 15 {
			addTown(towns, graph)
		} else {
			removeLastTown(towns, graph)
		}
		rwlock.Unlock()
		time.Sleep(100 * time.Millisecond)
	}
}

func PriceWorker(towns *int, graph *[][]int, rwlock *sync.RWMutex) {
	for {
		rwlock.Lock()
		var randPrice = rand.Intn(MAX_PRICE)
		var randFrom = random.Intn(*towns)
		var randTo = random.Intn(*towns)
		if (*graph)[randFrom][randTo] == 0 && (*graph)[randTo][randFrom] == 0 {
			changePrice(graph, randFrom, randTo, randPrice)
		}
		rwlock.Unlock()
		time.Sleep(100 * time.Millisecond)
	}
}

func DFS(graph [][]int, from int, to int) int {
	if from == to {
		return 0
	}
	visited := make(map[int]bool)
	for i := 0; i < len(graph); i++ {
		visited[i] = false
	}
	visited[from] = true
	return dfs(graph, from, to, visited, 0)

}

func dfs(graph [][]int, from int, to int, visited map[int]bool, cost int) int {
	if from == to {
		return cost
	}
	for i := 0; i < len(graph[from]); i++ {
		if graph[from][i] >= 0 {
			if i == to {
				return cost + graph[from][i]
			} else if !visited[i] {
				visited[i] = true
				res := dfs(graph, i, to, visited, cost+graph[from][i])
				if res >= 0 {
					return res
				}
			}
		}
	}
	return -1

}

func FinderWorker(towns *int, graph *[][]int, rwlock *sync.RWMutex) {
	for {
		rwlock.RLock()
		var randFrom = random.Intn(*towns)
		var randTo = random.Intn(*towns)
		cost := DFS(*graph, randFrom, randTo)
		if cost == -1{
			fmt.Printf("No path from %d to %d", randFrom, randTo)
		}else {
			fmt.Printf("Path from %d to %d costs %d", randFrom, randTo, cost)
		}
		rwlock.RUnlock()
		time.Sleep(1000 * time.Millisecond)
	}
}

func main() {
	var graph [][]int
	var towns = 0
	var rwlock = &sync.RWMutex{}
	for i := 0; i < 3; i++ {
		addTown(&towns, &graph)
	}

	go PathWorker(&towns, &graph, rwlock)
	go TownsWorker(&towns, &graph, rwlock)
	go PriceWorker(&towns, &graph, rwlock)
	FinderWorker(&towns, &graph, rwlock)


}

