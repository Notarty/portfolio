#!/bin/bash
docker image pull clock
docker image pull sae103-html2pdf
docker image pull sae103-php

docker volume create sae103
docker container run -d -v sae103:/work --name sae103-forever clock
docker container cp src1.c sae103-forever:/work
docker container cp src2.c sae103-forever:/work
docker container cp src3.c sae103-forever:/work
docker container cp gendoc-tech.php sae103-forever:/work
docker container cp gendoc-user.php sae103-forever:/work
docker container cp gendoc-tech.php sae103-forever:/work
docker container cp doc.md sae103-forever:/work

docker container run --rm -v sae103:/work --name sae103-php sae103-php php gendoc-tech.php 2.7.4
docker container run --rm -v sae103:/work --name sae103-php sae103-php php gendoc-user.php 2.7.4

docker container run --rm -v sae103:/work --name sae103-html2pdf -t sae103-html2pdf "html2pdf doc-tech-2.7.4.html doc-tech-2.7.4.pdf"
docker container run --rm -v sae103:/work --name sae103-html2pdf -t sae103-html2pdf "html2pdf doc-user-2.7.4.html doc-user-2.7.4.pdf"

docker container exec sae103-forever mkdir /work/les_genies_du_ponant_2.7.4
docker container exec sae103-forever cp /work/src1.c /work/les_genies_du_ponant_2.7.4
docker container exec sae103-forever cp /work/src2.c /work/les_genies_du_ponant_2.7.4
docker container exec sae103-forever cp /work/src3.c /work/les_genies_du_ponant_2.7.4
docker container exec sae103-forever cp /work/doc-tech-2.7.4.pdf /work/les_genies_du_ponant_2.7.4
docker container exec sae103-forever cp /work/doc-user-2.7.4.pdf /work/les_genies_du_ponant_2.7.4

docker container exec sae103-forever mv /work/les_genies_du_ponant_2.7.4 /

docker container exec sae103-forever tar czvf les_genies_du_ponant_2.7.4.tgz les_genies_du_ponant_2.7.4

docker container cp sae103-forever:/les_genies_du_ponant_2.7.4.tgz .

docker container stop sae103-forever
docker container rm sae103-forever
docker volume rm sae103
