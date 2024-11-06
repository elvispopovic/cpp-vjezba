Jednostavan "Hello World" HTTP posluzitelj napisan u jeziku C++ koristeci C++ REST SDK. Slusa dolazne HTTP GET zahtjeve i odgovara JSON porukom koju onda browser prikazuje. Izradjeno prema uputama za C++ kontejner u Dockeru [C++ Language Guide](https://docs.docker.com/language/cpp/).

## API

Kada stigne GET zahtjev, posluzitelj odgovara JSON objektom:

```json
{
    "poruka": "Hello World!"
}
```

## Potrebno za Docker compose

Slijedi sadrzaj datoteke [Dockerfile](Dockerfile) za Hello C++ aplikaciju:

```Dockerfile
# Use the official Ubuntu image as the base image
FROM ubuntu:latest

# Set the working directory in the container
WORKDIR /app

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    libcpprest-dev \
    libboost-all-dev \
    libssl-dev \
    cmake

# Kopira se izvorni kod .cpp u kontejner
COPY hello.cpp .

# Kompilira se C++ kod (hello.cpp)
RUN g++ -o ok_api ok_api.cpp -lcpprest -lboost_system -lboost_thread -lboost_chrono -lboost_random -lssl -lcrypto

# Otvara se port za REST API
EXPOSE 8080

# Kada se kontejner pokrene, ova naredba pokrece aplikaciju
CMD ["./hello"]
```

Kako bi se pokrenula Docker Compose, potrebno je stvoriti YAML datoteku `compose.yml`.

Ovdje je sadrzaj `compose.yml` datoteke:

```yaml
services:
  hello:
    image: cpp-hello-docker
    build:
      context: .
      dockerfile: Dockerfile
    ports:
      - "8080:8080"
```

Kako bi se bildao i pokrenuo Docker image koristeci Docker Compose, koristi se naredba:

```bash
docker-compose up
```

Ovo ce stvoriti Docker image i pokrenuti ga, mapirajuci kontejnerski port 8080 na port 8080 domacina. 
Sada mozete koristiti API by posjetom na URL `http://localhost:8080` unutar browsera.

## Doprinosi

Svaki povratni komentar i doprinos su dobro dosli!

## Prema MIT licenci

[MIT License](LICENSE)
