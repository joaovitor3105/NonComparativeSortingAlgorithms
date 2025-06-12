package Structures

type ListLinear struct {
    data     []int
    size     int
    capacity int
}

func NewListLinear(capacity int) *ListLinear {
    return &ListLinear{
        data:     make([]int, capacity),
        size:     0,
        capacity: capacity,
    }
}

func (l *ListLinear) Add(value int) {
    if l.size < l.capacity {
        l.data[l.size] = value
        l.size++
    }
}

func (l *ListLinear) ToArray() []int {
    result := make([]int, l.size)
    copy(result, l.data[:l.size])
    return result
}

func (l *ListLinear) FromArray(arr []int) {
    l.size = 0
    for _, v := range arr {
        if l.size < l.capacity {
            l.data[l.size] = v
            l.size++
        }
    }
}

func (l *ListLinear) Size() int {
    return l.size
}