from sys import argv as comandos
import random
MAXIMO_CARAC_TWEET = 280

def main():
	""" """
	diccionario = {}
	lista_trending = []
	with open("tweets_prueba.csv", encoding = "utf-8") as tweets:
		procesar_archivo(tweets, lista_trending, diccionario)
		print(diccionario)
		if comandos[1] == "generar":
			texto = generar(diccionario)
			print(f"Tweet:\n{texto}\n")
			if preguntar_favorito() == True:
				agregar_favoritos(texto)
		if comandos[1] == "trending":
			imprimir_trending()
		if comandos[1] == "favoritos":
			imprimir_favoritos()

def procesar_archivo(tweets, lista_trending, diccionario):
	"""Recibe el archivo y lo ordena en diccionario por usuario y a su vez a usuario le agrega otro diccionario 
	con las palabras como clave y listas de palabras siguientes como valores"""
	for linea in tweets:
		linea = linea.rstrip("\n")
		usuario, tweet = linea.split("\t")
		if usuario in comandos[2:] or comandos[2:] == None:
			procesar_tweets(tweet, lista_trending, diccionario)
	if len(diccionario) < 1:
		print("Ingrese un usuario valido")		


def procesar_tweets(tweet, lista_trending, diccionario):
	"""Recibe el tweet y el usuario que lo escribio. Por usuario en el diccionario crea como llave cada palabra y de valor la palabra que le siga a la misma"""
	palabras = tweet.split(" ")
	generar_trending(palabras, lista_trending)
	for i in range(len(palabras)):
		if palabras[i] not in diccionario:
			try:
				diccionario[palabras[i]] = [palabras[i + 1]]
			except IndexError:
				diccionario[palabras[i]] = ""
		else:
			try:
				diccionario[palabras[i]].append(palabras[i + 1])
			except IndexError:
				diccionario[palabras[i]] = ""

def generar(diccionario):
	"""Recibe una cadena vacia y le agrega palabras aleatoriamente utilizando las cadenas de Markov. Limite del tweet es MAXIMO_CARAC_TWEET y devuelve el tweet generado."""
	contador = 0
	tweet_generado = ""
	while True:
		if contador < 1:
			palabra = random.choice(list(diccionario.keys()))
		palabra = random.choice(diccionario[palabra])
		if palabra == "" or not len(tweet_generado) + len(palabra) <= MAXIMO_CARAC_TWEET:
			break
		tweet_generado = tweet_generado + palabra + " "
		contador += 1
	tweet_generado = retocar_tweet(tweet_generado)
	return tweet_generado

def retocar_tweet(tweet_generado):
	"""Recibe el tweet_generado y pone mayuscula la primera letra y un "." al final, devuelve el tweet_generado."""
	try:
		tweet_generado = tweet_generado[0].upper() + tweet_generado[1:]
	except AttributeError:
		pass
	tweet_lista = list(tweet_generado)
	tweet_lista[-1] = "."
	tweet_generado = "".join(tweet_lista)
	return tweet_generado

def generar_trending(palabras, lista_trending):
	"""Recibe las palabras que componen el tweet y se fija cual es precedida por "#" y la agrega a la lista_trending, luego la devuelve """
	for palabra in palabras:
		if palabra[0] == "#" and palabra not in lista_trending:
			lista_trending.append(palabra)
	return lista_trending

def agregar_favoritos(texto):
	"""Recibe el texto y lo agrega al final del archivo favorito.csv y le avisa al usuario que lo hizo al finalizar"""
	with open("favoritos.csv", "a", encoding = "utf-8") as favs:
		favs.write(texto + "\n")
		print("Se ha agregado a Favoritos")

def preguntar_favorito():
	"""Pregunta al usuario si quiere guardar el texto, en caso afirmativo devuelve True, en cualquier otro caso devuelve False"""
	respuesta = input("Quiere añadir este Tweet a favoritos? [s / n]: ")
	if respuesta == "s":
		return True
	return False

def imprimir_favoritos():
	"""Imprime el contenido del archivo favoritos de abajo hacia arriba"""
	with open("favoritos.csv", encoding = "utf-8") as favoritos:
		lista_favs = []
		llenar_lista_favs(lista_favs, favoritos)
		lista_favs = lista_favs_invertida(lista_favs)
		try:
			for i in range(int(comandos[2])):
				print(f"{lista_favs[i]} \n ")
		except IndexError:
			for tweet in lista_favs:
				print(tweet + "\n")

def llenar_lista_favs(lista_favs, favoritos):
	for linea in favoritos:
		linea = linea.rstrip("\n")
		lista_favs.append(linea)

def lista_favs_invertida(lista_favs):
	"""Recibe la lista_favs, la invierte y la devuelve"""
	for i in range(len(lista_favs) // 2):
		primero = lista_favs[i]
		ultimo = lista_favs[-i - 1]
		lista_favs[i] = ultimo
		lista_favs[-i - 1] = primero
	return lista_favs

def imprimir_trending():
	if comandos[2].isdigit():
		for i in range(comandos[2]):
			print(i)








main()
  