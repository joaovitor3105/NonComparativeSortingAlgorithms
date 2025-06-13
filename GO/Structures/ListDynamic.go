package Structures

type NodeList struct {
    value int
    next  *NodeList
}

type ListDynamic struct {
    head *NodeList
    tail *NodeList  // ← ADICIONADO: ponteiro para o último elemento
    size int
}

func NewListDynamic() *ListDynamic {
    return &ListDynamic{
        head: nil,
        tail: nil,
        size: 0,
    }
}

func (l *ListDynamic) Add(value int) {
    newNode := &NodeList{value: value, next: nil}
    
    if l.head == nil {
        l.head = newNode
        l.tail = newNode  // ← Primeiro elemento é head e tail
    } else {
        l.tail.next = newNode  // ← O(1) - adiciona direto no final!
        l.tail = newNode       // ← Atualiza tail
    }
    l.size++
}

func (l *ListDynamic) ToArray() []int {
    result := make([]int, l.size)
    current := l.head
    i := 0
    
    for current != nil {
        result[i] = current.value
        current = current.next
        i++
    }
    
    return result
}

func (l *ListDynamic) FromArray(arr []int) {
    l.head = nil
    l.tail = nil  // ← Resetar tail também
    l.size = 0
    
    for _, v := range arr {
        l.Add(v)
    }
}

func (l *ListDynamic) Size() int {
    return l.size
}