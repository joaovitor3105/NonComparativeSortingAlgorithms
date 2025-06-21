#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <map>
#include <memory>
#include <list>
#include <stack>
#include <queue>
#include <iomanip>
#include <algorithm>
#include <numeric>

// --- Suposição de Dependências (para o código compilar) ---
// Normalmente estariam em arquivos .hpp separados.
namespace CountingSort {
    std::vector<int> sort(std::vector<int> data) {
        if (data.empty()) return {};
        int max_val = *std::max_element(data.begin(), data.end());
        std::vector<int> counts(max_val + 1, 0);
        for (int val : data) counts[val]++;
        std::vector<int> sorted_data;
        sorted_data.reserve(data.size());
        for (int i = 0; i <= max_val; i++) {
            for (int j = 0; j < counts[i]; j++) {
                sorted_data.push_back(i);
            }
        }
        return sorted_data;
    }
} // namespace CountingSort

// --- NOVO: Estrutura de Teste Sistemático ---

// NOVO: Interface comum para todas as estruturas de dados
class DataStructure {
public:
    virtual ~DataStructure() = default;
    virtual void insert(int value) = 0;
    virtual std::vector<int> toVector() const = 0;
    virtual void fromVector(const std::vector<int>& data) = 0;
    virtual std::string getName() const = 0;
    virtual std::string getType() const = 0;
    virtual void clear() = 0;
};

// --- Implementações das 6 Estruturas de Dados ---

class ListaEstatica : public DataStructure {
    std::vector<int> data;
public:
    void insert(int value) override { data.push_back(value); }
    std::vector<int> toVector() const override { return data; }
    void fromVector(const std::vector<int>& vec) override { data = vec; }
    std::string getName() const override { return "Lista Estatica"; }
    std::string getType() const override { return "estatico"; }
    void clear() override { data.clear(); }
};

class ListaDinamica : public DataStructure {
    std::list<int> data;
public:
    void insert(int value) override { data.push_back(value); }
    std::vector<int> toVector() const override { return {data.begin(), data.end()}; }
    void fromVector(const std::vector<int>& vec) override { data.assign(vec.begin(), vec.end()); }
    std::string getName() const override { return "Lista Dinamica"; }
    std::string getType() const override { return "dinamico"; }
    void clear() override { data.clear(); }
};

class PilhaEstatica : public DataStructure {
    std::vector<int> data;
public:
    void insert(int value) override { data.push_back(value); }
    std::vector<int> toVector() const override { return data; }
    void fromVector(const std::vector<int>& vec) override { data = vec; }
    std::string getName() const override { return "Pilha Estatica"; }
    std::string getType() const override { return "estatico"; }
    void clear() override { data.clear(); }
};

class PilhaDinamica : public DataStructure {
    std::list<int> data;
public:
    void insert(int value) override { data.push_front(value); } // LIFO
    std::vector<int> toVector() const override { return {data.begin(), data.end()}; }
    void fromVector(const std::vector<int>& vec) override { data.assign(vec.begin(), vec.end()); }
    std::string getName() const override { return "Pilha Dinamica"; }
    std::string getType() const override { return "dinamico"; }
    void clear() override { data.clear(); }
};

class FilaEstatica : public DataStructure {
    std::vector<int> data;
public:
    void insert(int value) override { data.push_back(value); }
    std::vector<int> toVector() const override { return data; }
    void fromVector(const std::vector<int>& vec) override { data = vec; }
    std::string getName() const override { return "Fila Estatica"; }
    std::string getType() const override { return "estatico"; }
    void clear() override { data.clear(); }
};

class FilaDinamica : public DataStructure {
    std::list<int> data;
public:
    void insert(int value) override { data.push_back(value); } // FIFO
    std::vector<int> toVector() const override { return {data.begin(), data.end()}; }
    void fromVector(const std::vector<int>& vec) override { data.assign(vec.begin(), vec.end()); }
    std::string getName() const override { return "Fila Dinamica"; }
    std::string getType() const override { return "dinamico"; }
    void clear() override { data.clear(); }
};


// --- Funções de Medição e Exibição ---

// NOVO: Mede o tempo de um ciclo completo: inserir -> converter -> ordenar -> reconverter
double medirDesempenho(DataStructure& estrutura, const std::vector<int>& dados) {
    auto start = std::chrono::high_resolution_clock::now();

    estrutura.clear();
    for (int val : dados) {
        estrutura.insert(val);
    }
    auto vec = estrutura.toVector();
    auto sorted_vec = CountingSort::sort(vec);
    estrutura.fromVector(sorted_vec);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    return elapsed.count();
}

// NOVO: Calcula a memória teórica usada pela estrutura
size_t calculatePreciseMemoryUsage(const DataStructure& estrutura, int numElementos) {
    if (numElementos == 0) return 0;
    if (estrutura.getType() == "estatico") {
        return static_cast<size_t>(numElementos) * sizeof(int);
    } else {
        // Para std::list, cada nó tem o valor, um ponteiro para o próximo e um para o anterior
        size_t node_size = sizeof(int) + 2 * sizeof(void*);
        return static_cast<size_t>(numElementos) * node_size;
    }
}

// NOVO: Exibe a tabela de resumo final
void exibirTabelaResumoFinal(
    const std::vector<std::string>& nomes,
    const std::map<std::string, std::map<int, double>>& tempos,
    const std::map<std::string, std::map<int, size_t>>& memorias,
    const std::vector<int>& volumes)
{
    std::cout << "\n\n";
    std::cout << "                                         TABELA RESUMO FINAL\n";
    std::cout << std::string(120, '=') << std::endl;

    // Cabeçalho
    std::cout << std::left << std::setw(22) << "Estrutura" << " | " << std::setw(10) << "Tipo" << " |";
    for (int volume : volumes) {
        std::cout << std::right << std::setw(12) << volume << " |";
    }
    std::cout << "\n" << std::string(120, '-') << std::endl;

    // Seção de Tempo
    std::cout << "\nTEMPO (ms):\n";
    for (const auto& nome : nomes) {
        std::string tipo = (nome.find("Estatica") != std::string::npos) ? "estatico" : "dinamico";
        std::cout << std::left << std::setw(22) << nome << " | " << std::setw(10) << tipo << " |";
        const auto& resultados_tempo = tempos.at(nome);
        for (int volume : volumes) {
            std::cout << std::right << std::fixed << std::setprecision(2) << std::setw(12) << resultados_tempo.at(volume) << " |";
        }
        std::cout << std::endl;
    }

    // Seção de Memória
    std::cout << "\nMEMORIA (MB):\n";
     for (const auto& nome : nomes) {
        std::string tipo = (nome.find("Estatica") != std::string::npos) ? "estatico" : "dinamico";
        std::cout << std::left << std::setw(22) << nome << " | " << std::setw(10) << tipo << " |";
        const auto& resultados_memoria = memorias.at(nome);
        for (int volume : volumes) {
            double memoria_mb = static_cast<double>(resultados_memoria.at(volume)) / (1024.0 * 1024.0);
            std::cout << std::right << std::fixed << std::setprecision(2) << std::setw(12) << memoria_mb << " |";
        }
        std::cout << std::endl;
    }
    std::cout << std::string(120, '=') << std::endl;
}

// --- Função Principal do Benchmark ---

int main() {
    // ALTERADO: Lógica principal para rodar o benchmark sistemático
    std::cout << "================================================================" << std::endl;
    std::cout << "      ANÁLISE DE PERFORMANCE - C++ - COUNTING SORT" << std::endl;
    std::cout << "================================================================" << std::endl;

    const std::vector<int> VOLUMES_TESTE = {100, 1000, 10000, 100000, 1000000};
    
    // Preparar as estruturas para o teste
    std::vector<std::unique_ptr<DataStructure>> estruturas;
    estruturas.push_back(std::make_unique<ListaEstatica>());
    estruturas.push_back(std::make_unique<ListaDinamica>());
    estruturas.push_back(std::make_unique<PilhaEstatica>());
    estruturas.push_back(std::make_unique<PilhaDinamica>());
    estruturas.push_back(std::make_unique<FilaEstatica>());
    estruturas.push_back(std::make_unique<FilaDinamica>());

    std::vector<std::string> nomesEstruturas;
    for(const auto& s : estruturas) nomesEstruturas.push_back(s->getName());

    // Estruturas para armazenar resultados
    std::map<std::string, std::map<int, double>> resultadosTempo;
    std::map<std::string, std::map<int, size_t>> resultadosMemoria;

    for (int volume : VOLUMES_TESTE) {
        // Gerar dados de teste (em um cenário real, ler do CSVReader)
        std::cout << "\n--- GERANDO " << volume << " ENTRADAS DE TESTE ---" << std::endl;
        std::vector<int> dados;
        dados.reserve(volume);
        for (int i = 0; i < volume; ++i) dados.push_back(i % 50); // Dados simulados

        for (auto& estrutura_ptr : estruturas) {
            std::cout << "Testando " << std::left << std::setw(25) << estrutura_ptr->getName() << "... ";
            
            double tempo = medirDesempenho(*estrutura_ptr, dados);
            size_t memoria = calculatePreciseMemoryUsage(*estrutura_ptr, volume);

            resultadosTempo[estrutura_ptr->getName()][volume] = tempo;
            resultadosMemoria[estrutura_ptr->getName()][volume] = memoria;

            std::cout << "Concluido! (" << std::fixed << std::setprecision(2) << tempo << " ms)" << std::endl;
        }
    }

    exibirTabelaResumoFinal(nomesEstruturas, resultadosTempo, resultadosMemoria, VOLUMES_TESTE);

    return 0;
}