drop schema if exists "colleges" cascade;
create schema colleges;
set schema 'colleges';

CREATE TABLE _region (
    code_region VARCHAR(30) PRIMARY KEY,
    libelle_region VARCHAR(30) UNIQUE
);

CREATE TABLE _academie (
    code_academie int PRIMARY KEY,
    lib_academie VARCHAR(30) UNIQUE
);

CREATE TABLE _departement (
    code_departement VARCHAR(30) PRIMARY KEY,
    nom_departement VARCHAR(30) UNIQUE,
    code_region VARCHAR(30)
);

ALTER TABLE _departement ADD CONSTRAINT fk_inclut FOREIGN KEY (code_region) REFERENCES _region(code_region);

CREATE TABLE _commune (
    code_insee VARCHAR(30) PRIMARY KEY,
    nom_commune VARCHAR(30) UNIQUE,
    code_departement VARCHAR(30)
);

ALTER TABLE _commune ADD CONSTRAINT fk_se_situe FOREIGN KEY (code_departement) REFERENCES _departement(code_departement);

CREATE TABLE _etablissement (
    uai VARCHAR(30) PRIMARY KEY,
    nom_etablissement VARCHAR(30),
    secteur VARCHAR(30),
    code_postal VARCHAR(30),
    lattitude float,
    longitude float,
    code_insee VARCHAR(30),
    code_academie int,
    code_nature VARCHAR(30),
    code_quartier_prioritaire VARCHAR(30)
);

CREATE TABLE _classe (
    id_classe VARCHAR(30) PRIMARY KEY
);

CREATE TABLE _type (
    code_nature VARCHAR(30) PRIMARY KEY,
    libelle_nature VARCHAR(30)
);

CREATE TABLE _quartier_prioritaire (
    code_quartier_prioritaire VARCHAR(30) PRIMARY KEY,
    nom_quartier_prioritaire VARCHAR(30)
);

CREATE TABLE _annee (
    annee_scolaire VARCHAR(30) PRIMARY KEY
);

CREATE TABLE _caracteristiques_tout_etablissement (
    uai VARCHAR(30),
    effectifs int,
    ips float,
    ecart_type_ips float,
    ep VARCHAR(30),
    annee_scolaire VARCHAR(30),
    PRIMARY KEY (uai, annee_scolaire)
);

ALTER TABLE _caracteristiques_tout_etablissement ADD CONSTRAINT fk_caract_tout_etab_etablissement FOREIGN KEY (uai) REFERENCES _etablissement(uai);
ALTER TABLE _caracteristiques_tout_etablissement ADD CONSTRAINT fk_caract_tout_etab_annee FOREIGN KEY (annee_scolaire) REFERENCES _annee(annee_scolaire);

CREATE TABLE _caracteristiques_college (
    uai VARCHAR(30),
    nbre_eleves_hors_segpa_hors_ulis int,
    nbre_eleves_segpa_ulis int,
    nbre_classes_segpa_ulis int,
    annee_scolaire VARCHAR(30),
    PRIMARY KEY (uai, annee_scolaire)
);

ALTER TABLE _caracteristiques_college ADD CONSTRAINT fk_caract_college_etablissement FOREIGN KEY (uai) REFERENCES _etablissement(uai);
ALTER TABLE _caracteristiques_college ADD CONSTRAINT fk_caract_college_annee FOREIGN KEY (annee_scolaire) REFERENCES _annee(annee_scolaire);

CREATE TABLE _caracteristiques_selon_classe (
    uai VARCHAR(30),
    nbre_eleves_hors_segpa_hors_ulis int,
    nbre_eleves_segpa int,
    nbre_eleves_ulis int,
    effectif_filles int,
    effectif_garcons int,
    annee_scolaire VARCHAR(30),
    id_classe VARCHAR(30),
    PRIMARY KEY (uai, annee_scolaire, id_classe)
);

ALTER TABLE _caracteristiques_selon_classe ADD CONSTRAINT fk_caract_classe_etablissement FOREIGN KEY (uai) REFERENCES _etablissement(uai);
ALTER TABLE _caracteristiques_selon_classe ADD CONSTRAINT fk_caract_classe_annee FOREIGN KEY (annee_scolaire) REFERENCES _annee(annee_scolaire);
ALTER TABLE _caracteristiques_selon_classe ADD CONSTRAINT fk_caract_classe_classe FOREIGN KEY (id_classe) REFERENCES _classe(id_classe);

ALTER TABLE _etablissement ADD CONSTRAINT fk_est_localise_dans FOREIGN KEY (code_insee) REFERENCES _commune(code_insee);
ALTER TABLE _etablissement ADD CONSTRAINT fk_depend_de FOREIGN KEY (code_academie) REFERENCES _academie(code_academie);
ALTER TABLE _etablissement ADD CONSTRAINT fk_etablissement_type FOREIGN KEY (code_nature) REFERENCES _type(code_nature);
ALTER TABLE _etablissement ADD CONSTRAINT fk_est_a_proximite_de FOREIGN KEY (code_quartier_prioritaire) REFERENCES _quartier_prioritaire(code_quartier_prioritaire);