import random
FILAS = 2
COLUMNAS = 2
MINAS = 1
PUNTOS_TABLERO = "."
LETRAS = ("A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "Ñ", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z")
BANDERA = "*"
ILUSTRACION_MINA = "o"
VALOR_MINAS = 9 #Representa el valor que se le asigna al casillero que contiene una mina en una matriz que no ve el usuario
#DOS_CARAC = 2 # Carac = caracteres
#TRES_CARAC = 3
CUATRO_CARAC = 4
DOS_DIG_COLUMNAS = 10 # Representa cuando el numero de columnas es igual o mayor a dos digitos
INSTRUCCIONES = f"""
##################################################################################################################################################
# Bienvenido al Buscaminas: El juego consiste en despejar todas las casillas, ingresando las coordenadas del casillero, que no oculten una mina. #
# Las casillas sin minas tienen un número, el cual indica la cantidad de minas que hay en las casillas circundantes.                             #
# Si se descubre una casilla con una mina se pierde la partida.                                                                                  #
# Se puede colocar/quitar una marca en las casillas que pienses que hay una mina escribiendo: "{BANDERA}A8" (sin espacios, ni comillas).                 #
# Suerte!!                                                                                                                                       #
##################################################################################################################################################
"""

def main():
	"""Buscaminas(leer INSTRUCCIONES); crea la base del juego y lo desarrolla; soporta un maximo de 27*99."""
	print(INSTRUCCIONES)
	CENTINELA = "#"
	tablero_visual = crear_tablero_visual()
	numerador = crear_numerador()
	tablero_logico = crear_tablero_logico()	
	while True:
		imprimir_tablero(numerador, tablero_visual)
		if se_termino_el_juego(tablero_visual):
			print("Felicidades, ganaste!!")
			return
		entrada = pedir_entrada(CENTINELA)
		if entrada == CENTINELA:
			return
		if entrada == "":
			continue	
		if entrada[0] == BANDERA:
			ancho_entrada = 3
			index_entrada = 1
			if entrada_es_valida(entrada, index_entrada, ancho_entrada):
				procesar_jugada_bandera(entrada, tablero_visual, ancho_entrada)
		else:
			ancho_entrada = 2
			index_entrada = 0		
			if entrada_es_valida(entrada, index_entrada, ancho_entrada):
				if not procesar_jugada(entrada, tablero_logico, tablero_visual, ancho_entrada):
					imprimir_tablero(numerador, tablero_visual)
					print("Pisaste una mina, perdiste")
					return	

def crear_tablero_visual():
	"""Crea una matriz recibiendo sus dimensiones(FILAS, COLUMNAS) y en cada elemento de la misma se pone un '.'; devuelve la matriz"""
	tablero_visual = []
	for _ in range(FILAS):
		tablero_visual.append([PUNTOS_TABLERO] * COLUMNAS)	
	return tablero_visual
	
def crear_tablero_logico():
	"""Crea la misma matriz que crear_tablero_visual pero con minas y valores de la proximidad de cada punto a las minas. 
	Devuelve esa matriz como tablero_logico."""
	tablero_logico = []
	for _ in range(FILAS):
		tablero_logico.append([0] * COLUMNAS)
	contador = 0
	while True:
		a = random.randint(0, FILAS - 1)
		b = random.randint(0, COLUMNAS - 1)
		if contador == MINAS:
			break
		if tablero_logico[a][b] == VALOR_MINAS:
			continue
		tablero_logico[a][b] = VALOR_MINAS
		contador += 1	
	evaluar_proximidad_minas(tablero_logico)		
	return tablero_logico
	
def es_posible(x, y):
	"""Define si una coordenada es valida, osea si existe en la matriz, devuelve True en caso afirmativo, en caso contrario devuelve False"""
	if x in range(FILAS) and y in range(COLUMNAS):
		return True
	return False	

def entrada_es_valida(entrada, index_entrada, ancho_entrada):
	"""Verifica si la entrada del usuario cumple los requisitos para modificar el tablero_visual y devuelve True en caso de 
	ser afirmativo, en caso contrario devuelve False"""
	if COLUMNAS < DOS_DIG_COLUMNAS and len(entrada) == ancho_entrada and entrada[index_entrada] in LETRAS:
		if LETRAS.index(entrada[index_entrada]) <= FILAS:
			if entrada[index_entrada + 1].isdigit() and int(entrada[index_entrada + 1]) <= COLUMNAS:
				return True
	if COLUMNAS >= DOS_DIG_COLUMNAS and len(entrada) == (ancho_entrada + 1) and entrada[index_entrada] in LETRAS:
		if LETRAS.index(entrada[index_entrada]) <= FILAS: 
			if entrada[index_entrada + 1:].isdigit() and int(entrada[index_entrada + 1:]) <= COLUMNAS:
				return True
	return False

def imprimir_tablero(numerador, tablero_visual):
	"""Imprime el tablero_visual con una fila numerando las columnas y una columna numerando las filas"""
	print("")
	print("  ".join(numerador[0:10]), " ".join(numerador[10:]))
	for i in range(FILAS):
		Fila = "  ".join(tablero_visual[i])
		filas_letras = LETRAS[i]
		print(f"{filas_letras}  {Fila}")	

def pedir_entrada(CENTINELA):
	"""Pide al usuario una entrada de coordenadas para modificar el tablero_visual, indicando fila y columna, la convierte a mayusculas y la devuelve"""
	entrada = input( f"\nIngrese coordenadas (ej: A1)[ '{CENTINELA}' para salir, '{BANDERA}' para bandera (ej: *A1), cant. minas: {MINAS}]: ")
	entrada = entrada.upper()
	return entrada

def crear_numerador():
	"""Crea la fila que numera las columnas y la devuelve"""
	numerador = [" ",]
	for i in range(1, COLUMNAS + 1):
		numerador.append(str(i))
	return numerador

def procesar_jugada_bandera(entrada, tablero_visual, ancho_entrada):
	"""Recibe una entrada del usuario y la desarma para poder procesar la jugada, tambien recibe el tablero_visual donde va a realizar la jugada"""
	x = LETRAS.index(entrada[1])
	if len(entrada) == ancho_entrada:
		y = int(entrada[2]) - 1
		hacer_jugada_bandera(x, y, tablero_visual)
	else:
		y = int(entrada[2:]) -1
		hacer_jugada_bandera(x, y, tablero_visual)

def hacer_jugada_bandera(x, y, tablero_visual):
	"""Recibe los parametros x, y, y el tablero_visual a realizar la jugada y modifica el mismo colocando banderas en las coordenadas solicitadas,
	si ya hay una BANDERA la reemplaza por PUNTOS_TABLERO"""
	if tablero_visual[x][y] == BANDERA:
		tablero_visual[x][y] = PUNTOS_TABLERO
	else:
		tablero_visual[x][y] = BANDERA

def procesar_jugada(entrada, tablero_logico, tablero_visual, ancho_entrada):
	"""Recibe una entrada del usuario y la desarma para poder procesar la jugada, tambien recibe un tablero_visual y un tablero_logico"""
	x = LETRAS.index(entrada[0])
	if len(entrada) == ancho_entrada:
		y = int(entrada[1]) - 1
		return hacer_jugada(x, y, tablero_logico, tablero_visual)
	y = int(entrada[1:]) -1
	return hacer_jugada(x, y, tablero_logico, tablero_visual)

def hacer_jugada(x, y, tablero_logico, tablero_visual):
	"""Recibe los parametros x, y, y verifica si en la entrada del usuario en el punto del tablero_visual secundario si hay una mina devuelve False, 
	en caso contrario reemplaza en el tablero_visual el valor que se encontraba en la misma posicion en el tablero_visual de minas y valores; si hay una BANDERA devuelve True """
	if tablero_visual[x][y] == BANDERA:
		return True
	if tablero_logico[x][y] == VALOR_MINAS:
		tablero_visual[x][y] = ILUSTRACION_MINA
		return False
	tablero_visual[x][y] = str(tablero_logico[x][y])
	return True

def se_termino_el_juego(tablero_visual):
	"""Recibe el tablero_visual y evalua si solo quedan minas en el tablero_visual. En caso afirmativo devuelve True, en cualquier otro caso devuelve False"""
	contador = 0
	for fila in tablero_visual:
		for elemento in fila:
			if elemento == PUNTOS_TABLERO or elemento == BANDERA:
				contador += 1
	if contador == MINAS:
		return True
	return False	

def evaluar_proximidad_minas(tablero_logico):
	"""Recibe el tablero_logico y evalua la proximidad de las minas en cada posicion, modifica la matriz con las minas poniendo los valores de proximidad"""	
	for x in range(FILAS):
		for y in range(COLUMNAS):
			if tablero_logico[x][y] == VALOR_MINAS:
				continue
			evaluar_proximidad(x, y, tablero_logico)

def evaluar_proximidad(x, y, tablero_logico):
	for k in (-1, 0, 1):
		for h in (-1, 0, 1):
			if es_posible(x + k, y + h) and tablero_logico[x + k][y + h] == VALOR_MINAS:
				tablero_logico[x][y] += 1

main()
