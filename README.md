# Proyecto de Control con LCD, Teclado Matricial y EEPROM

Este proyecto utiliza un microcontrolador con un teclado matricial, una pantalla LCD y memoria EEPROM para implementar un sistema de menús interactivos y almacenamiento de configuraciones.

## Descripción

El programa permite al usuario interactuar con un sistema de menús en un LCD usando un teclado matricial de 4x4. Cada tecla tiene una función específica para navegar, seleccionar opciones y modificar configuraciones almacenadas en la memoria EEPROM. Adicionalmente, el sistema puede leer el estado de pines y realizar acciones en función de ellos.

### Características
- **Interfaz de usuario** con menú principal y submenús.
- **Teclado matricial 4x5** para navegación y selección.
- **Pantalla LCD I2C** para mostrar menús y valores.
- **Almacenamiento EEPROM** para guardar configuraciones persistentes.
- **Sensores y pines de entrada digital** para lecturas dinámicas.

## Requisitos

- **Hardware:**
  - Microcontrolador (Arduino u otro compatible).
  - Pantalla LCD con interfaz I2C.
  - Teclado matricial 4x5.
  - EEPROM integrada en el microcontrolador.
  - Sensores o entradas digitales conectados a los pines especificados.

- **Software:**
  - Arduino IDE.
  - Librerías necesarias:
    - `LiquidCrystal_I2C`
    - `Wire`
    - `Keypad`
    - `EEPROM`

## Instalación

1. Instala las librerías necesarias en tu Arduino IDE.
2. Conecta los componentes de hardware según el esquema de pines en el código:
   - Filas del teclado: pines 8-12.
   - Columnas del teclado: pines 4-7.
   - LCD I2C: dirección `0x27`.
   - Pines digitales para entradas: `camon1`-`camon4` (pines 0-3), `ten1`-`ten4` (pines A0-A3).

3. Sube el código al microcontrolador.

## Uso

1. **Encendido:** Al iniciar el sistema, se mostrará un mensaje de bienvenida en el LCD.
2. **Navegación por menús:**
   - Usa las teclas `U` y `A` para moverte hacia arriba y abajo en el menú.
   - Presiona `E` para seleccionar una opción.
   - Usa `S` para regresar al menú anterior.
3. **Configuración de valores:**
   - Selecciona un campo para editar.
   - Ingresa los valores numéricos con las teclas del teclado matricial.
   - Confirma con `E`.

