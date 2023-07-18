#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Classe Data
class Data {
public:
    int dia, mes, ano, hora, minuto;

    Data(int d, int m, int a, int h, int min) {
        dia = d;
        mes = m;
        ano = a;
        hora = h;
        minuto = min;
    }

    // Construtor padrão adicionado
    Data() {
        dia = 0;
        mes = 0;
        ano = 0;
        hora = 0;
        minuto = 0;
    }
};

// Classe Cliente
class Cliente {
public:
    string nome;

    Cliente(const string& n) {
        nome = n;
    }
};

// Classe Veiculos
class Veiculos : public Data {
public:
    int codigo;
    string placa;
    string modelo;
    Cliente* cliente;

    Veiculos(int Cod, string Pla, string Mod, int d, int m, int a, int h, int min, Cliente* cli)
        : Data(d, m, a, h, min) {
        codigo = Cod;
        placa = Pla;
        modelo = Mod;
        cliente = cli;
    }
};

// Função de entrada de veículo
void EntradaDeVeiculo(vector<Veiculos>& vetor) {
    string modelo, placa;
    int dia, mes, ano, hora, minuto;

    cout << "Digite o modelo do carro: ";
    cin >> modelo;
    cout << "Digite a placa do carro: ";
    cin >> placa;
    cout << "Digite o dia da entrada: ";
    cin >> dia;
    cout << "Digite o mês da entrada: ";
    cin >> mes;
    cout << "Digite o ano da entrada: ";
    cin >> ano;
    cout << "Digite a hora da entrada: ";
    cin >> hora;
    cout << "Digite o minuto da entrada: ";
    cin >> minuto;

    int cod = vetor.size() + 1;  // Atribui o próximo código disponível
    Veiculos entrar(cod, placa, modelo, dia, mes, ano, hora, minuto, nullptr);
    vetor.push_back(entrar);
}

void SalvarVeiculosEmArquivo(const vector<Veiculos>& vetor, const string& nomeArquivo) {
    ofstream arquivo(nomeArquivo);
    
    if (arquivo.is_open()) {

        for (const auto& veiculo : vetor) {
            arquivo << "Código: " << veiculo.codigo << endl;
            arquivo << "Modelo: " << veiculo.modelo << endl;
            arquivo << "Placa: " << veiculo.placa << endl;
            arquivo << "Data de entrada: " << veiculo.dia << "/" << veiculo.mes << "/" << veiculo.ano << " " << veiculo.hora << ":" << veiculo.minuto << endl;
            arquivo << endl;
        }

        arquivo.close();
        cout << "Os veículos foram salvos no arquivo: " << nomeArquivo << endl;
    } else {
        cout << "Não foi possível abrir o arquivo para salvar os veículos." << endl;
    }
}

// Saida de veiculos
void calcularDiferencaTempo(Veiculos& veiculo, Veiculos& veiculoSaiu) {
    int horaEntrada = veiculo.hora + veiculo.mes * 720 + veiculo.ano * 8760;
    int horaSaida = veiculoSaiu.hora + veiculoSaiu.mes * 720 + veiculoSaiu.ano * 8760;

    int horaDiferenca = horaSaida - horaEntrada;

    cout << "Tempo de permanência: " << horaDiferenca << " horas." << endl;
}

void SaidaDeVeiculo(vector<Veiculos>& vetor) {
    string placa;
    int dia, mes, ano, hora, minuto;
    bool encontrado;
    vector<Veiculos> sairam;

    cout << "Digite a placa do veículo que deseja remover: ";
    cin >> placa;
    cout << "Digite o dia da entrada: ";
    cin >> dia;
    cout << "Digite o mês da entrada: ";
    cin >> mes;
    cout << "Digite o ano da entrada: ";
    cin >> ano;
    cout << "Digite a hora da entrada: ";
    cin >> hora;
    cout << "Digite o minuto da entrada: ";
    cin >> minuto;

    for (auto it = vetor.begin(); it != vetor.end(); it++) {
        if (it->placa == placa) {
            encontrado = true;
            Veiculos veiculoSaiu = *it;
            veiculoSaiu.ano = ano;
            veiculoSaiu.dia = dia;
            veiculoSaiu.hora = hora;
            veiculoSaiu.minuto = minuto;
            veiculoSaiu.mes = mes;
            sairam.push_back(veiculoSaiu);
            calcularDiferencaTempo(*it, veiculoSaiu);
            vetor.erase(it);
            break;
        } else {
            encontrado = false;
        }
    }

    if (encontrado) {
        cout << "Veículo com placa " << placa << " removido do estacionamento." << endl;
    } else {
        cout << "Veículo com placa " << placa << " não encontrado no estacionamento." << endl;
    }
}

// Função para cadastrar um cliente
Cliente CadastrarCliente() {
    string nome;

    cout << "Digite o nome do cliente: ";
    cin >> nome;

    return Cliente(nome);
}

// Função para verificar se o cliente é cadastrado
bool VerificarCliente(const vector<Cliente>& clientes, const string& nomeCliente) {
    for (const auto& cliente : clientes) {
        if (cliente.nome == nomeCliente) {
            return true;
        }
    }

    return false;
}

// Função para obter desconto do cliente
double ObterDesconto(const vector<Cliente>& clientes, const string& nomeCliente) {
    for (const auto& cliente : clientes) {
        if (cliente.nome == nomeCliente) {
            return 0.9; // Desconto de 10% (0.9) aplicado para clientes cadastrados
        }
    }

    return 1.0; // Sem desconto para clientes não cadastrados
}

// MAIN!!!!
int main() {
    int opcao;
    vector<Veiculos> vetor;
    vector<Cliente> clientes;

    do {
        cout << "1) Registro de entrada de veiculo" << endl
             << "2) Registro de saida de veiculo (a partir da placa; atualiza a data de saida e valor pago)" << endl
             << "3) Geracao de um arquivo com os veiculos que ainda estao no estacionamento" << endl
             << "4) Cadastrar um cliente" << endl
             << "5) Sair" << endl;
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "Entrar" << endl;
                EntradaDeVeiculo(vetor);
                break;
            case 2:
                cout << "Sair" << endl;
                SaidaDeVeiculo(vetor);
                break;
            case 3: {
                string nomeArquivo;
                cout << "Digite o nome do arquivo: ";
                cin >> nomeArquivo;
                SalvarVeiculosEmArquivo(vetor, nomeArquivo);
                break;
            }
            case 4: {
                cout << "Cadastrar cliente" << endl;
                Cliente cliente = CadastrarCliente();
                clientes.push_back(cliente);
                break;
            }
            case 5:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida." << endl;
                break;
        }
    } while (opcao != 5);

    return 0;
}
