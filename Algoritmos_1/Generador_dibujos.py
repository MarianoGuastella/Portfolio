import sys
import math

class _Punto:
	"""Representación de un punto en el plano en
	coordenadas cartesianas (x, y)"""
	def __init__(self, x=0, y=0):
		"""Constructor de Punto. x e y deben ser numéricos"""
		self.x = x 
		self.y = y

	def __str__(self):
		"""Devuelve la representación del Punto como
		cadena de texto."""
		return "({}, {})".format(self.x, self.y)

	def __repr__(self):
		"""Devuelve la representación formal del Punto como
		cadena de texto."""
		return "Punto({}, {})".format(self.x, self.y)

class Pluma:
	"""Representa una pluma de escribir. Tiene las operaciones para cambiar el color,
	el ancho y el estado de escritura"""
	def __init__(self, color="black", ancho=10, escribir=True):
		"""Crea una pluma con un color, un ancho y un estado de escritura"""
		self.color = color
		self.ancho = ancho
		self.escribir = escribir

	def color(self, color="black"):
		"""Cambia el valor del atributo color"""
		self.color = color

	def ancho(self, ancho=10):
		"""Cambia el valor del atributo ancho"""
		self.ancho = ancho

	def escribir(self):
		"""Cambia el estado del atributo escribir"""
		if self.escribir:
			self.escribir = False
		else:
			self.escribir = True

class Tortuga:
	"""Representa un puntero con operaciones de adelante, adelante_sin_escribir, derecha,
	 izquierda, pluma_arriba y pluma_abajo."""
	def __init__(self, direccion=math.pi/2, posicion=_Punto(), pluma=Pluma()):
		"""Crea la tortuga en una posicion(un punto (x,y)), con un sentido(angulo en rads)
		y un estado de la pluma."""
		self.direccion = direccion
		self.posicion = posicion
		self.pluma = pluma

	def adelante(self, distancia):
		"""Hace avanzar a la tortuga, lo que recibe por parametro,
		por el plano en la misma direccion que estaba avanzando previamente."""
		self.posicion.x += distancia * math.cos(self.direccion)
		self.posicion.y += distancia * math.sin(self.direccion)

	def derecha(self, angulo):
		"""Gira la orientacion hacia la derecha, sentido de las agujas del reloj."""
		self.direccion -= angulo

	def izquierda(self, angulo):
		"""Gira la orientacion hacia la izquierda, sentido contrario a 
		las agujas del reloj."""
		self.direccion += angulo

	def pluma_arriba(self):
		"""Cambia el estado de la pluma a 'arriba'."""
		self.pluma.escribir = False

	def pluma_abajo(self):
		"""Cambia el estado de la pluma a 'abajo'."""
		self.pluma.escribir = True

	def adelante_sin_escribir(self, distancia):
		"""Hace avanzar a la tortuga por el plano sin escribir"""
		self.pluma_arriba()
		self.adelante(distancia)

	def rotar_180(self, _ ):
		"""Gira la direccion 180 grados o pi"""
		self.direccion -= math.pi

class Pila:
	"""Representa una pila con operaciones de apilar, desapilar, ver tope y
	verificar si está vacía."""
	def __init__(self):
		"""Crea una pila vacía."""
		self.items = []

	def apilar(self, x):
		"""Apila el elemento x."""
		self.items.append(x)

	def desapilar(self):
		"""Desapila el ultimo elemento y lo devuelve.
		Si la pila está vacía levanta una excepción."""
		if self.esta_vacia():
			raise ValueError("La pila está vacía")
		return self.items.pop()

	def esta_vacia(self):
		"""Devuelve True si la lista está vacía, False en caso contario."""
		return len(self.items) == 0

	def ver_tope(self):
		"""Devuelve el ultimo item de la pila, si no hay devuelve None"""
		if len(self.items) == 0:
			return None
		return self.items[-1]

def apilar_tortuga(pila_tortugas):
	"""Recibe una pila. Hace una copia (copia los valores de los atributos)de la ultima tortuga que
	fue apilada, luego la apila"""
	tope = pila_tortugas.ver_tope()
	posicion = _Punto(tope.posicion.x, tope.posicion.y)
	direccion = tope.direccion 
	pluma = Pluma(tope.pluma.color, tope.pluma.ancho, tope.pluma.escribir)
	tortuga = Tortuga(direccion, posicion, pluma)
	pila_tortugas.apilar(tortuga)

def dibujar(instrucciones, angulo):
	"""Recibe unas instrucciones y un angulo. Ejecuta las insturcciones utilizando una serie de comandos segun corresponda
	Devuelve una lista con cada conjunto de (x,y) que forman una linea del dibujo, ademas devuelve el par de 
	X minimo y maximo y el par de Y minimo y maximo:::: "Y": Tortuga.adelante, "X": Tortuga.adelante,::::::"""
	X_min_max, Y_min_max = [0, 0], [0, 0] #El primer elemento ([0]) de c/u es el min y el segundo ([1]) el max
	pila_tortugas = Pila()
	pila_tortugas.apilar(Tortuga())
	dibujo = [] #conjunto de pares de (x,y) que conforman las lineas del dibujo
	distancia = 100
	instrucciones_recibidas_no_definidas = [] #Almacena aquellas instrucciones que no estan definidas
	comandos_logicos = { "[": apilar_tortuga, "]": Pila.desapilar }
	comandos_avanzar = { "F": Tortuga.adelante, "G": Tortuga.adelante, "f": Tortuga.adelante_sin_escribir, 
	"g":  Tortuga.adelante_sin_escribir}
	comandos_angulares = { "+": Tortuga.derecha, "-": Tortuga.izquierda, "|": Tortuga.rotar_180 }
	for i in range(len(instrucciones)):
		if instrucciones[i] not in comandos_logicos and instrucciones[i] not in comandos_avanzar and \
		instrucciones[i] not in comandos_angulares:
			if instrucciones[i] not in instrucciones_recibidas_no_definidas:
				print(f"{instrucciones[i]} no esta establecido")              #Estas dos lineas pueden sacarse
				instrucciones_recibidas_no_definidas.append(instrucciones[i]) #Pero yo preferi mostrar lo que no esta establecido
			continue
		tortuga = pila_tortugas.ver_tope()
		if instrucciones[i] in comandos_avanzar:
			x_inicial, y_inicial = tortuga.posicion.x, tortuga.posicion.y
			tortuga.pluma_abajo()
			metodo = comandos_avanzar[instrucciones[i]]
			metodo(tortuga, distancia)
			if not tortuga.pluma.escribir:
				continue
			agregar_linea_dibujo(dibujo, tortuga, x_inicial, y_inicial)
			calcular_extremos(X_min_max, Y_min_max, pila_tortugas)
		elif instrucciones[i] in comandos_angulares:
			metodo = comandos_angulares[instrucciones[i]]
			metodo(tortuga, angulo)
		else:
			comando = comandos_logicos[instrucciones[i]]
			comando(pila_tortugas)
	return dibujo, X_min_max, Y_min_max

def calcular_extremos(X_min_max, Y_min_max, pila_tortugas):
	"""Se fija si el (x,y) del ultimo elemento de la pila de tortugas son extremos y en caso positivo los guarda en 
	X_min_max, Y_min_max segun corresponda (pisa los valores anteriores). En caso negativo no hace nada"""
	tortuga = pila_tortugas.ver_tope()
	if tortuga.posicion.x > X_min_max[1]:
		X_min_max[1] = tortuga.posicion.x
	if tortuga.posicion.x < X_min_max[0]:
		X_min_max[0] = tortuga.posicion.x
	if tortuga.posicion.y > Y_min_max[1]:
		Y_min_max[1] = tortuga.posicion.y
	if tortuga.posicion.y < Y_min_max[0]:
		Y_min_max[0] = tortuga.posicion.y

def agregar_linea_dibujo(dibujo, tortuga, x_inicial, y_inicial):
	"""Recibe las coordenadas iniciales de una tortuga, mira las actuales(finales) y agrega al dibujo la linea entre estos
	dos puntos"""
	x_final = tortuga.posicion.x
	y_final = tortuga.posicion.y
	dibujo.append((f""" <line x1="{x_inicial}" y1="{- y_inicial}" x2="{x_final}" y2="{- y_final}" stroke-width= 
		"{tortuga.pluma.ancho}" stroke="{tortuga.pluma.color}" />\n """))

def escribir_svg(dibujo, nombre_svg, X_min_max, Y_min_max):
	"""Recibe el nombre para el svg, el dibujo, los X min/max y los Y min/max. Crea un archvio svg con el nombre,
	con los x e y max/min determina el ViewBox y en el mismo escribe todos las lineas que conforman el dibujo."""
	ancho = X_min_max[1] - X_min_max[0] #El primer elemento ([0]) de c/u es el min y el segundo ([1]) el max
	alto = -Y_min_max[0] + Y_min_max[1] #El primer elemento ([0]) de c/u es el min y el segundo ([1]) el max
	with open(nombre_svg, "w") as svg:
		svg.write(f""" <svg viewBox= "{X_min_max[0] - 100} {-Y_min_max[1] - 100} {ancho + 150} {alto + 250}" 
		xmlns="http://www.w3.org/2000/svg">\n """)
		for i in range(len(dibujo)): #Cada i es una nueva posicion
			svg.write(dibujo[i])
		svg.write("</svg>")

def iterar_axioma(axioma, iteraciones, reglas):
	"""Recibe el axioma, las reglas y la cantidad de iteraciones. Aplica las reglas al axioma segun 
	tantas iteraciones se indiquen, devuelve el axioma iterado."""
	for i in range(iteraciones):
		cadena_auxiliar = ""
		for j in range(len(axioma)):
			cadena_auxiliar += reglas.get(axioma[j], axioma[j])
		axioma = cadena_auxiliar
	return axioma

def procesar_archivo(path_sl):
	"""Procesa el archivo .sl y devuelve el angulo convertido a radianes, axiomas y 
	reglas (predecesores/sucesores)."""
	angulo, axioma, reglas = leer_archivo_sl(path_sl)
	angulo = math.radians(angulo)
	return angulo, axioma, reglas

def leer_archivo_sl(path_sl):
	"""Lee el path_sl y devuelve el angulo, axiomas y reglas (predecesores/sucesores)."""
	reglas = {}
	with open(path_sl) as sl:
		angulo = sl.readline().rstrip("\n")
		axioma = sl.readline().rstrip("\n")
		angulo = float(angulo)
		for linea in sl:
			if linea.rstrip("\n") == None:
				break
			linea = linea.rstrip("\n")
			predecesores, sucesores = linea.split(" ") 
			reglas[predecesores] = sucesores
	return angulo, axioma, reglas

def imprimir_formato():
	"""Imprime una cadena que muestra un formato especifico"""
	print(""" El archivo tiene que tener el formato: \n
		"<ángulo>" \n "<axioma>" \n 
		<predecesor1> <sucesor1> \n
		<predecesor2> <sucesor2> \n
		<predecesor3> <sucesor3>""")

def faltan_argumentos(elemento1, elemento2, elemento3):
	"""Recibe tres elementos y verifica que los tres sean distintos de None, lo cual implicaria
	que alguno no tiene valor"""
	if elemento1 == None or elemento2 == None or elemento3 == None:
		return True
	return False

def asignar(comandos):
	"""Recibe una lista de comandos, asigna el elemento iterador, el nombre del svg y el path del archivo .sl.
	Devuelve los tres elementos."""
	nombre_svg, iteraciones, path_sl = None, None, None
	for elemento in comandos:
		if ".svg" in elemento:
			nombre_svg = elemento
		if ".sl" in elemento:
			path_sl = elemento
		if elemento.isdigit():
			iteraciones = int(elemento)
	return nombre_svg, iteraciones, path_sl

def main():
	"""Crea un svg con un dibujo, siguiendo unas instrucciones pasadas por un archivo"""
	nombre_svg, iteraciones, path_sl = asignar(sys.argv[1:])
	if faltan_argumentos(nombre_svg, iteraciones, path_sl):
		print("Ingrese nombre.sl, iteraciones y nombre.svg")
		return
	try:
		angulo, axioma, reglas = procesar_archivo(path_sl)
	except FileNotFoundError:
		print("No se encuentra el archivo")
		return
	except ValueError:
   	    print("El angulo tiene que ser un número")
   	    return
	if faltan_argumentos(angulo, axioma, reglas):
		imprimir_formato()
		return
	instrucciones = iterar_axioma(axioma, iteraciones, reglas)
	dibujo, X_min_max, Y_min_max = dibujar(instrucciones, angulo) 
	escribir_svg(dibujo, nombre_svg, X_min_max, Y_min_max)

main()