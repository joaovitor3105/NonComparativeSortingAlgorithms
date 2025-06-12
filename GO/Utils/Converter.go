package Utils

// Interface para todas as estruturas
type DataStructure interface {
    ToArray() []int
    FromArray([]int)
    Size() int
}

// Função auxiliar para converter qualquer estrutura para array
func StructureToArray(ds DataStructure) []int {
    return ds.ToArray()
}

// Função auxiliar para converter array para qualquer estrutura
func ArrayToStructure(arr []int, ds DataStructure) {
    ds.FromArray(arr)
}