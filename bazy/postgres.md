# Fajne rzeczy

## Instalowanie postgres
sudo apt isntall postgresql postgresql-contrib
## Sprawdzenie statusu działania postgres
sudo systemctl status postgresql
# Coś fajnego

## Wejście w katalog postgres i odpalenie konfigów postgres
cd \etc\postgresql
code .

## Jakieś wejście w postgres w konsoli
sudo -i -u postgres

## jakies polecenia w tym miejscu
\du
ALTER USER postgres PASSWORD 'postgres'
