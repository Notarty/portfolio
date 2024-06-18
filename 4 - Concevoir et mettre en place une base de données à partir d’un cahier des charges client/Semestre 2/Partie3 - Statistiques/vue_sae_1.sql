set schema 'colleges2';
drop view vue_sae;


create or replace view vue_sae as
select distinct taux_de_reussite_g,
nombre_eleves_segpa,
nombre_eleves_ulis,
_6emes_garcons + _5emes_garcons + _4emes_garcons + _3emes_garcons as garcons,
_6eme_filles + _5eme_filles + _4eme_filles + _3eme_filles as filles
from _temp_fr_en_college_effectif_niveau_sexe_lv
inner join _temp_fr_en_indicateurs_valeur_ajoutee_colleges on _temp_fr_en_indicateurs_valeur_ajoutee_colleges.uai = _temp_fr_en_college_effectif_niveau_sexe_lv.numero_college 
where nombre_eleves_segpa is not null 
and nombre_eleves_ulis is not null
and nombre_eleves_segpa <> 0
and nombre_eleves_ulis <> 0
;

WbExport -file=colleges_sans_0.csv
         -outputDir=/home/etuinfo/npommereul/Documents/Bdd/sae_204
         -type=text
         -sourceTable=vue_sae
         -schema=colleges2
         -delimiter=';'
         -header=true
         -keyColumns=No_Dossier,formation
         -dateFormat='d/M/y'
         -timestampFormat='d/M/y H:m:s'
         ;