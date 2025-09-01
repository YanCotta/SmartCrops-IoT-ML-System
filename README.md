# SmartCrops-IoT-ML-System

Um projeto de IoT-ML para agricultura inteligente: Nós duplos de ESP32 (sensor via ESP-NOW, gateway para MQTT/Ubidots) coletam dados de temperatura, umidade e umidade do solo. Um modelo de ML analisa o rendimento da safra e classifica a saúde da planta em tempo real. Código em Python, Notebooks e C++. Desenvolvido para a Fase 5 do primeiro ano do curso de tecnologia em IA/ML da FIAP. Contém ambos entregáveis mandatórios e ambos "Ir Aléns".

## Status das Entregas do Projeto - 2/4 concluídas

### Entrega 1 - CONCLUÍDA (Análise de Rendimento Agrícola)

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

## Metodologia de Análise

1.  **Análise Exploratória de Dados (EDA)**: Análise estatística e visualização abrangente
2.  **Análise de Clusterização**: Clusterização K-means com otimização pelo método do cotovelo
3.  **Detecção de Outliers**: Isolation Forest para identificação de anomalias
4.  **Modelagem de Regressão**: Comparação de 5 modelos com avaliação de desempenho
5.  **Importância das Features**: Análise com Random Forest revelando a dominância do tipo de cultura
6.  **Inteligência de Negócios**: Recomendações estratégicas e roteiro de implementação


##  Hardware Setup & Firmware Deployment (Ir Além 1 & 2) - A Step-by-Step Changelog

This section documents the end-to-end process of setting up the physical IoT hardware, from initial troubleshooting to a fully functional data pipeline.

### Part 1: Environment Setup & Troubleshooting

The first challenge was to establish a stable connection between the development environment (Ubuntu/VS Code) and the ESP32 hardware, which had never been done before on this machine.

**1. Initial Setup & Diagnosis**
* **Action**: Installed VS Code, the PlatformIO extension, and necessary system drivers.
* **Problem**: Upon connecting the ESP32, the OS did not recognize the device or assign a communication port. The PlatformIO device list was empty.
* **Initial Hypotheses**: Suspected issues with USB cable, drivers, or user permissions.

**2. Systematic Debugging**
* **Action**: Followed a systematic troubleshooting process to isolate the issue.
* **Steps Taken**:
    * Confirmed the user was in the `dialout` and `tty` groups for correct permissions.
    * Installed the PlatformIO `99-udev-rules` to ensure the Linux kernel could correctly identify the hardware.
    * Used terminal commands like `lsusb` and `ls /dev/tty*` to diagnose the connection status at the hardware and OS levels.
* **Key Finding**: The `ls /dev/tty*` command consistently showed that no communication port was being created, pointing to a physical layer issue.

**3. The Breakthrough: Physical Layer Solution**
* **Action**: After exhausting software solutions, the focus shifted to the physical hardware.
* **Solution**: The faulty component was identified as a **"charge-only" micro-USB cable**. Replacing it with a proper **data-transfer cable** instantly solved the connection issue.
* **Proof**: The `/dev/ttyACM0` port immediately appeared after connecting the ESP32 with the new cable.

### Part 2: Firmware Deployment & Configuration

With a stable connection, the next phase was to create and deploy the firmware.

**4. Professional Project Structure**
* **Action**: Created two distinct PlatformIO projects (`sensor-node` and `gateway-node`) and organized them within a VS Code Workspace.
* **Best Practices Implemented**:
    * **Secure Credentials**: Created a `.env` file to store Wi-Fi and Ubidots credentials securely, preventing them from being committed to Git.
    * **Clean Repository**: Updated the root `.gitignore` file to exclude temporary build files (`.pio/`) and local settings (`.vscode/`, `.env`).

**5. Obtaining Unique MAC Addresses**
* **Action**: Created and uploaded a temporary `MAC_Finder` firmware to each ESP32 individually.
* **Purpose**: To retrieve the unique hardware MAC address of each board, which is required for the ESP-NOW communication protocol.

**6. Flashing the Final Firmware**
* **Action**: Configured the main `sensor-node` and `gateway-node` firmware with the MAC address and credentials. Successfully compiled and uploaded the code to each respective board.

### Part 3: Final Assembly & System Test (In Progress)

This section will document the final build and live test of the complete system.

**7. Circuit Assembly**
* **Action**: The `sensor-node` was wired with DHT22 and soil moisture sensors. The `gateway-node` was wired with an LED and a buzzer for alerts.
* **Verification**: Double-checked all connections against the provided schematics to ensure correctness.

**8. Live Data Transmission & Verification**
* **Action**: Powered on both nodes. The Sensor Node began collecting data and sending it to the Gateway via ESP-NOW. The Gateway successfully connected to Wi-Fi and began publishing the data to the Ubidots cloud platform via MQTT.
* **Result**: The end-to-end data pipeline is fully operational.
