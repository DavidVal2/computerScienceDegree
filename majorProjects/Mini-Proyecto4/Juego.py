import pygame
import random
import sys

def Iniciador():
    # Inicializar Pygame
    pygame.init()

    # Configuración de la pantalla y colores
    PosicionT = 40
    TableroT = 15
    PantallaT = PosicionT * TableroT
    Programa = pygame.display.set_mode((PantallaT, PantallaT))
    pygame.display.set_caption("Parchis de David")

    # Colores
    WHITE = (255, 255, 255)
    BLACK = (0, 0, 0)
    RED = (255, 0, 0)
    GREEN = (0, 255, 0)
    BLUE = (0, 0, 255)
    YELLOW = (255, 255, 0)
    GRAY = (150, 150, 150)
    BROWN = (139, 69, 19)

    # Cargar imágenes de dados
    DadoI = [
        pygame.image.load(f"Dado{i}.png") for i in range(1, 7)
        
    ]

    # Cargar imagen de la ficha
    C1_Imagen = pygame.image.load("C1.png")
    C1_Imagen = pygame.transform.scale(C1_Imagen, (PosicionT, PosicionT) )
    A1_Imagen = pygame.image.load("A1.png")
    A1_Imagen = pygame.transform.scale(A1_Imagen, (PosicionT, PosicionT) )
    B1_Imagen = pygame.image.load("B1.png")
    B1_Imagen = pygame.transform.scale(B1_Imagen, (PosicionT, PosicionT) )
    D1_Imagen = pygame.image.load("D1.png")
    D1_Imagen = pygame.transform.scale(D1_Imagen, (PosicionT, PosicionT) )

    # Devolver variables clave
    return Programa, PantallaT, PosicionT, TableroT, DadoI, WHITE, BLACK, RED, GREEN, BLUE, YELLOW, GRAY, BROWN, C1_Imagen, A1_Imagen, B1_Imagen, D1_Imagen
 
Programa, PantallaT, PosicionT, TableroT, DadoI, WHITE, BLACK, RED, GREEN, BLUE, YELLOW, GRAY, BROWN, C1_Imagen, A1_Imagen, B1_Imagen, D1_Imagen = Iniciador()

# Variables para el estado del juego
C1 = None       # Posición de C1 (empieza sin valor)
C1_active = False  # Indica si C1 ha sido activado
A1 = None       
A1_active = False  
B1 = None       
B1_active = False  
D1 = None       
D1_active = False  
ValorDados = (0, 0)  # Valores de los dados


def TirarDado():
    """Simula el lanzamiento de dos dados y devuelve dos valores entre 1 y 6."""
    return random.randint(1, 6), random.randint(1, 6)

def DibujarDado(ValorDados):
    """Dibuja los dos dados en la esquina inferior derecha del tablero."""
    (ValorD1, ValorD2) = ValorDados
    
    # Calcular posiciones para los dos dados en la esquina inferior derecha
    dice1_pos = (PantallaT - PosicionT * 4, PantallaT - PosicionT * 3)
    dice2_pos = (PantallaT - PosicionT * 2, PantallaT - PosicionT * 3)
    
    # Cargar las imágenes correspondientes a los valores de los dados
    Dado1I = DadoI[ValorD1 - 1]
    Dado2I = DadoI[ValorD2 - 1]
    
    # Dibujar las imágenes de los dados en pantalla
    Programa.blit(Dado1I, Dado1I.get_rect(topleft=dice1_pos))
    Programa.blit(Dado2I, Dado2I.get_rect(topleft=dice2_pos))

def Camino_Rojo():
    return [[0 , 0, 0, 0, 0, 0, 0,52,51, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0, 0,53,50, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0, 0,54,49, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0, 0,55,48, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0, 1,56,47, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0, 2,57,46, 0, 0, 0, 0, 0, 0],
            [9 , 8, 7, 6, 5, 4, 3,58,45,44,43,42,41,40,39],
            [10, 0, 0, 0, 0, 0, 0,59, 0, 0, 0, 0, 0, 0,38],
            [11,12,13,14,15,16,17, 0,31,32,33,34,35,36,37],
            [0 , 0, 0, 0, 0, 0,18, 0,30, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,19, 0,29, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,20, 0,28, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,21, 0,27, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,22, 0,26, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,23,24,25, 0, 0, 0, 0, 0, 0]]

def Camino_Azul():
    return [[0 , 0, 0, 0, 0, 0,11,10, 9, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,12, 0, 8, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,13, 0, 7, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,14, 0, 6, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,15, 0, 5, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,16, 0, 4, 0, 0, 0, 0, 0, 0],
            [23,22,21,20,19,18,17, 0, 3, 2, 1, 0, 0, 0, 0],
            [24, 0, 0, 0, 0, 0, 0,59,58,57,56,55,54,53,52],
            [25,26,27,28,29,30,31, 0,45,46,47,48,49,50,51],
            [0 , 0, 0, 0, 0, 0,32, 0,44, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,33, 0,43, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,34, 0,42, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,35, 0,41, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,36, 0,40, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,37,38,39, 0, 0, 0, 0, 0, 0]]

def Camino_Amarillo():
    return [[0 , 0, 0, 0, 0, 0,25,24,23, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,26, 0,22, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,27, 0,21, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,28, 0,20, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,29, 0,19, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,30, 0,18, 0, 0, 0, 0, 0, 0],
            [37,36,35,34,33,32,31, 0,17,16,15,14,13,12,11],
            [38, 0, 0, 0, 0, 0, 0,59, 0, 0, 0, 0, 0, 0,10],
            [39,40,41,42,43,44,45,58, 3, 4, 5, 6, 7, 8, 9],
            [0 , 0, 0, 0, 0, 0,46,57, 2, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,47,56, 1, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,48,55, 0, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,49,54, 0, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,50,53, 0, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,51,52, 0, 0, 0, 0, 0, 0, 0]]

def Camino_Verde():
    return [[0 , 0, 0, 0, 0, 0,39,38,37, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,40, 0,36, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,41, 0,35, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,42, 0,34, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,43, 0,33, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0,44, 0,32, 0, 0, 0, 0, 0, 0],
            [51,50,49,48,47,46,45, 0,31,30,29,28,27,26,25],
            [52,53,54,55,56,57,58,59, 0, 0, 0, 0, 0, 0,24],
            [ 0, 0, 0, 0, 1, 2, 3, 0,17,18,19,20,21,22,23],
            [0 , 0, 0, 0, 0, 0, 4, 0,16, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0, 5, 0,15, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0, 6, 0,14, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0, 7, 0,13, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0, 8, 0,12, 0, 0, 0, 0, 0, 0],
            [0 , 0, 0, 0, 0, 0, 9,10,11, 0, 0, 0, 0, 0, 0]]


def DibujarTablero():
    Programa.fill(WHITE)
    for row in range(TableroT):
        for col in range(TableroT):
            color = WHITE
            # Asignar colores según la lógica anterior
            if row == 0 or row == TableroT - 1 or col == 0 or col == TableroT - 1:
                color = BROWN if not (row in {6, 7, 8} or col in {6, 7, 8}) else GRAY
            elif 1 <= row < 6 and 1 <= col < 6:
                color = RED
            elif 1 <= row < 6 and 9 <= col < 14:
                color = BLUE
            elif 9 <= row < 14 and 1 <= col < 6:
                color = GREEN
            elif 9 <= row < 14 and 9 <= col < 14:
                color = YELLOW
            elif row == 7 or col == 7:
                color = GRAY
            elif row == 7 or 9 and col == 4 or col == 10: #Seguros en horizontal
                color = GRAY
            elif col == 7 or 9 and row == 4 or row == 10: #Seguros en horizontal
                color = GRAY
            pygame.draw.rect(Programa, color, (col * PosicionT, row * PosicionT, PosicionT, PosicionT))
            pygame.draw.rect(Programa, BLACK, (col * PosicionT, row * PosicionT, PosicionT, PosicionT), 1)
    
    pygame.draw.rect(Programa, RED, (7 * PosicionT, 1 * PosicionT, PosicionT, 6 * PosicionT))
    pygame.draw.rect(Programa, GREEN, (1 * PosicionT, 7 * PosicionT, 6 * PosicionT, PosicionT))
    pygame.draw.rect(Programa, BLUE, (8 * PosicionT, 7 * PosicionT, 6 * PosicionT, PosicionT))
    pygame.draw.rect(Programa, YELLOW, (7 * PosicionT, 8 * PosicionT, PosicionT, 6 * PosicionT))

def DibujarC1(C1):
    matriz_roja = Camino_Rojo()
    for row in range(len(matriz_roja)):
        for col in range(len(matriz_roja[row])):
            if matriz_roja[row][col] == C1:
                Programa.blit(C1_Imagen, (col * PosicionT, row * PosicionT))
                return

def DibujarA1(A1):
    matriz_amarilla = Camino_Amarillo()
    for row in range(len(matriz_amarilla)):
        for col in range(len(matriz_amarilla[row])):
            if matriz_amarilla[row][col] == A1:
                Programa.blit(A1_Imagen, (col * PosicionT, row * PosicionT))
                return

def DibujarB1(B1):
    matriz_Azul = Camino_Azul()
    for row in range(len(matriz_Azul)):
        for col in range(len(matriz_Azul[row])):
            if matriz_Azul[row][col] == B1:
                Programa.blit(B1_Imagen, (col * PosicionT, row * PosicionT))
                return
            
def DibujarD1(D1):
    matriz_verde = Camino_Verde()
    if D1 == 1:
        Programa.blit(D1_Imagen, (4 * PosicionT, 8 * PosicionT))
    else:
        for row in range(len(matriz_verde)):
            for col in range(len(matriz_verde[row])):
                if matriz_verde[row][col] == D1:
                    Programa.blit(D1_Imagen, (col * PosicionT, row * PosicionT))
                    return
            
def Turno(Turno_actual):
    if Turno_actual == "Rojo":
        Turno_actual = "Verde"
        print("Turno de Verde")
    elif Turno_actual == "Verde":
        Turno_actual = "Amarillo"
        print("Turno de Amarillo")
    elif Turno_actual == "Amarillo":
        Turno_actual = "Azul"
        print("Turno de Azul")
    elif Turno_actual == "Azul":
        Turno_actual = "Rojo"
        print("Turno de Rojo")
    return Turno_actual
            
def Moverse(Turno, dice_roll):
    global A1, B1, C1, D1  # Asegúrate de que estas variables sean accesibles en la función

    if Turno == "Rojo":
        C1 = min(C1 + dice_roll, 59) if C1 is not None else None
    elif Turno == "Amarillo":
        A1 = min(A1 + dice_roll, 59) if A1 is not None else None
    elif Turno == "Azul":
        B1 = min(B1 + dice_roll, 59) if B1 is not None else None
    elif Turno == "Verde":
        D1 = min(D1 + dice_roll, 59) if D1 is not None else None

    if C1 == 59 or A1 == 59 or B1 == 59 or D1 == 59:
        print(f"¡El jugador {Turno} ha ganado!")
        pygame.quit()
        sys.exit()


def Verificador():
    global A1, B1, C1, D1
    
    if C1 is not None and D1 is not None:
        if C1-15 == D1:
            D1=1
            print("Comido!")
            DibujarD1()
    

def principal():
    global C1, C1_active, A1, A1_active, B1, B1_active, D1, D1_active, ValorDados
    running = True
    ValorDados = TirarDado()
    Turno_Actual = "Rojo"

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYDOWN: 
                if event.key == pygame.K_SPACE:
                    ValorDados = TirarDado()
                    if ValorDados[0] == ValorDados[1]:
                        print(f"Es par! El jugador {Turno_Actual} vuelve a tirar.")


                    # Activar la ficha solo si es el turno correcto y se saca doble
                    if Turno_Actual == "Rojo" and ValorDados[0] == ValorDados[1] and not C1_active:
                        C1 = 1
                        C1_active = True
                    elif Turno_Actual == "Amarillo" and ValorDados[0] == ValorDados[1] and not A1_active:
                        A1 = 1
                        A1_active = True
                    elif Turno_Actual == "Azul" and ValorDados[0] == ValorDados[1] and not B1_active:
                        B1 = 1
                        B1_active = True
                    elif Turno_Actual == "Verde" and ValorDados[0] == ValorDados[1] and not D1_active:
                        D1 = 1
                        D1_active = True
                elif event.key == pygame.K_q:
                    Moverse(Turno_Actual, ValorDados[0])
                    ValorDados = (0, ValorDados[1])
                elif event.key == pygame.K_e:
                    Moverse(Turno_Actual, ValorDados[1])
                    ValorDados = (ValorDados[0], 0)
                elif event.key == pygame.K_t:
                    Turno_Actual = Turno(Turno_Actual)

                # Cambia el turno solo después de que se haya movido la ficha
                Verificador()
                
                
        DibujarTablero()
        DibujarDado(ValorDados)
        
        DibujarC1(C1)
        
        DibujarA1(A1)
        DibujarB1(B1)
        DibujarD1(D1)
        pygame.display.flip()

principal() 