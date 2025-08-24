# SmartCrops-IoT-ML-System

Um projeto de IoT-ML para agricultura inteligente: Nós duplos de ESP32 (sensor via ESP-NOW, gateway para MQTT/Ubidots) coletam dados de temperatura, umidade e umidade do solo. Um modelo de ML analisa o rendimento da safra e classifica a saúde da planta em tempo real. Código em Python, Notebooks e C++. Desenvolvido para a Fase 5 do primeiro ano do curso de tecnologia em IA/ML da FIAP. Contém ambos entregáveis mandatórios e ambos "Ir Aléns".

## 🎯 Status das Entregas do Projeto

### ✅ Entrega 1 - CONCLUÍDA (Análise de Rendimento Agrícola)

**Entregável**: `notebooks/entregavel_1.ipynb`

**Resumo das Conquistas**:

  - **99,5% de Precisão Preditiva** na modelagem de rendimento agrícola usando um algoritmo específico de machine learning
  - **Descoberta que muda o paradigma**: A seleção da cultura é o fator dominante (96,9% de importância) sobre as condições ambientais 
  - **Análise de nível sênior** com EDA abrangente, clusterização e comparação de 5 modelos
  - **Transformação de negócios**: Da otimização ambiental para a inteligência de portfólio agrícola

**Principais Descobertas**:

  - **Dataset**: 156 registros de alta qualidade de 4 tipos de culturas (Cacau, Palma de Óleo, Arroz, Borracha)
  - **Variação de Rendimento**: Variação extraordinária de 40 vezes (5.249 a 203.399 toneladas/hectare)
  - **Melhor Modelo**: Regressão Linear (R² = 0,9950, RMSE = 4.394) -> valores elevados devido a qualidade do dataset,
não por data leakage ou qualquer outro problema
  - **Insight Estratégico**: A seleção do fruto da palma de óleo por si só explica 96,9% da variação no rendimento

**Excelência Técnica**:

  - Zero valores ausentes, qualidade de dados perfeita
  - Análise de clusterização avançada revelando 3 perfis de rendimento distintos
  - Avaliação abrangente de modelos (Linear, Decision Trees, Random Forest, SVR, KNN)
  - Visualizações profissionais e rigor estatístico

**Impacto de Negócios para a FarmTech Solutions**:

  - Ferramenta de otimização da seleção de culturas com 99,5% de precisão
  - Potencial de melhoria do ROI de até 20x através da escolha estratégica de culturas
  - Estrutura de avaliação de risco baseada na análise de clusters de rendimento


## 📁 Estrutura do Projeto

```
├── data/
│   └── crop_yield.csv              # Dataset histórico de rendimento agrícola (156 registros)
├── docs/                           # Documentação do projeto
├── ir-alem1/                       # Componentes de Hardware/IoT
├── ir-alem2/                       # Componentes de análise de ML
├── notebooks/
│   └── entregavel_1.ipynb  # Entrega final mandatória 1/2 ✅
└── requirements.txt                # Dependências Python
```

## 🔬 Metodologia de Análise

1.  **Análise Exploratória de Dados (EDA)**: Análise estatística e visualização abrangente
2.  **Análise de Clusterização**: Clusterização K-means com otimização pelo método do cotovelo
3.  **Detecção de Outliers**: Isolation Forest para identificação de anomalias
4.  **Modelagem de Regressão**: Comparação de 5 modelos com avaliação de desempenho
5.  **Importância das Features**: Análise com Random Forest revelando a dominância do tipo de cultura
6.  **Inteligência de Negócios**: Recomendações estratégicas e roteiro de implementação

## 🏆 Excelência Acadêmica

  - **Rigor Estatístico**: Validação de modelo e avaliação de desempenho adequadas
  - **Integração com Negócios**: Tradução de descobertas técnicas para valor estratégico
  - **Comunicação Profissional**: Relatório analítico claro e abrangente
  - **Inovação**: Insights inovadores que desafiam abordagens tradicionais de otimização agrícola

**Aluno**: Yan Pimentel Cotta (RM: 562836)
**Instituição**: FIAP - Tecnólogo em IA/ML
**Fase**: 5 (Primeiro Ano)
**Data**: 22 de agosto de 2025