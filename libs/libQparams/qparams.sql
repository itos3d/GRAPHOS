CREATE TABLE qp_params (
  id INTEGER,
  code VARCHAR(30) NOT NULL DEFAULT "", 
  name VARCHAR(50), 
  description VARCHAR(100),
  param_type INTEGER NOT NULL DEFAULT 0,  /* 0:continuous, 1:discrete */
  internal_unit INTEGER,
  default_value VARCHAR(30),
  domain_id INTEGER,
  param_category INTEGER,
  precision INTEGER DEFAULT 0,
  PRIMARY KEY (id),
  UNIQUE (code),
  FOREIGN KEY(internal_unit) REFERENCES qp_units(id),
  FOREIGN KEY(param_category) REFERENCES qp_categories(id),
  FOREIGN KEY(domain_id) REFERENCES qp_domains(id)
);

CREATE TABLE qp_units (
  id INTEGER,
  code VARCHAR(30) NOT NULL,
  name VARCHAR(50), 
  description VARCHAR(100),
  PRIMARY KEY (id),
  UNIQUE (code)
);

CREATE TABLE qp_categories (
  id INTEGER,
  code VARCHAR(30) NOT NULL,
  name VARCHAR(50),
  description VARCHAR(100),
  is_base_unit INTEGER NOT NULL,
  UNIQUE (code),
  PRIMARY KEY (id),
  UNIQUE (is_base_unit),
  FOREIGN KEY(is_base_unit) REFERENCES qp_units(id)
);

CREATE TABLE qp_categories_units (
  id INTEGER,
  id_category INTEGER,
  id_unit INTEGER,
  PRIMARY KEY (id),
  UNIQUE(id_category, id_unit),
  FOREIGN KEY(id_category) REFERENCES qp_categories(id),
  FOREIGN KEY(id_unit) REFERENCES qp_units(id)
);

CREATE TABLE qp_transformations (
  id INTEGER,
  code VARCHAR(30) NOT NULL,
  name VARCHAR(50),
  description VARCHAR(100),
  source_unit INTEGER,
  target_unit INTEGER,
  expression VARCHAR(100) NOT NULL,
  expression_inverse VARCHAR(100) NOT NULL,
  UNIQUE (code),
  PRIMARY KEY (id), 
  FOREIGN KEY(source_unit) REFERENCES qp_units(id),
  FOREIGN KEY(target_unit) REFERENCES qp_units(id)
);

CREATE TABLE qp_values (
  id INTEGER,
  code VARCHAR(30) NOT NULL,
  val VARCHAR(50), 
  description VARCHAR(100),
  PRIMARY KEY (id),
  UNIQUE (code)
);

CREATE TABLE qp_values_params (
  id INTEGER,
  id_value INTEGER,
  id_param INTEGER,
  PRIMARY KEY (id),
  UNIQUE (id_value, id_param),
  FOREIGN KEY(id_value) REFERENCES qp_values(id),
  FOREIGN KEY(id_param) REFERENCES qp_params(id)
);

CREATE TABLE qp_domains(
  id INTEGER,
  code VARCHAR(30) NOT NULL, 
  name VARCHAR(50), /*NUEVO*/
  min_value DOUBLE NOT NULL,
  max_value DOUBLE NOT NULL,
  PRIMARY KEY (id)
);

CREATE TABLE qp_apps (
  id INTEGER,
  code VARCHAR(30) NOT NULL,
  name VARCHAR(50),
  description VARCHAR(100),
  PRIMARY KEY (id)
);

CREATE TABLE qp_apps_params (
  id INTEGER,
  id_app INTEGER,
  id_param INTEGER,
  PRIMARY KEY (id),
  UNIQUE (id_app, id_param),
  FOREIGN KEY(id_app) REFERENCES qp_apps(id),
  FOREIGN KEY(id_param) REFERENCES qp_params(id)
);

CREATE TRIGGER on_delete_units_set_default_params AFTER DELETE ON qp_units
BEGIN
    UPDATE qp_params SET internal_unit=0 WHERE internal_unit=id;
END;

CREATE TRIGGER on_delete_domain_set_default_params AFTER DELETE ON
qp_domains
BEGIN
    UPDATE qp_params SET domain_id=0 WHERE domain_id=id;
END;

CREATE TRIGGER on_delete_categories_set_default_params AFTER DELETE ON
qp_categories
BEGIN
    UPDATE qp_params SET  param_category=0 WHERE param_category=id;
END;

CREATE TRIGGER on_delete_values_delete_values_params AFTER DELETE ON
qp_values
BEGIN
    DELETE FROM qp_values_params WHERE id_value=id;
END;

CREATE TRIGGER on_delete_apps_delete_apps_params AFTER DELETE ON qp_apps
BEGIN
    DELETE FROM qp_apps_params WHERE id_app=id;
END;

CREATE TRIGGER on_delete_units AFTER DELETE ON qp_units
BEGIN
    UPDATE qp_params SET internal_unit=0 WHERE internal_unit=id;
    DELETE FROM qp_transformations WHERE source_unit=id OR target_unit=id;
    DELETE FROM qp_categories WHERE is_base_unit=id;
    DELETE FROM qp_categories_units WHERE id_unit=id;
END;

insert into qp_domains (id,code, name, min_value, max_value) values
('0','withoutDomain','... without Domain','0','0');
insert into qp_units (id,code, name, description) values
('0','withoutUnit','... without Unit','Default value');
insert into qp_categories (id,code, name, description,is_base_unit) values
('0','withoutCategory','... without Category','Category for discrete
params','0');


