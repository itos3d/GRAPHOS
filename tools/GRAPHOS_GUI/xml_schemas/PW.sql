CREATE TABLE pw_projects (
  id INTEGER,
  name VARCHAR(50), 
  description VARCHAR(100),
  base_path VARCHAR(200),
  sparse_path VARCHAR(150),
  dense_path VARCHAR(150),
  ori_name VARCHAR(50),
  match_format INTEGER,
  metadata VARCHAR(5000),
  tiepoints_name VARCHAR(100),
  cloud_uuid VARCHAR(50),
  PRIMARY KEY (id),
  UNIQUE (name)
);

CREATE TABLE pw_images (
  id INTEGER,
  name VARCHAR(50),
  url VARCHAR(150),
  id_project INTEGER,
  id_camera INTEGER,
  id_active_model INTEGER,
  PRIMARY KEY (id),
  FOREIGN KEY(id_camera) REFERENCES pw_cameras(id),
  FOREIGN KEY(id_project) REFERENCES pw_projects(id) ON DELETE CASCADE,
  FOREIGN KEY(id_active_model) REFERENCES pw_camera_models(id) ON DELETE CASCADE
);

CREATE TABLE pw_terrain_points (
  id INTEGER,
  x DOUBLE,
  y DOUBLE,
  z DOUBLE,
  point_type INTEGER,
  id_project,
  name VARCHAR(50),
  PRIMARY KEY (id),
  FOREIGN KEY(id_project) REFERENCES pw_projects(id) ON DELETE CASCADE
); 

CREATE TABLE pw_image_points (
  id INTEGER,
  name VARCHAR(30),
  x DOUBLE,
  y DOUBLE,
  point_type INTEGER,
  id_image INTEGER,
  id_terrain_point INTEGER,
  PRIMARY KEY (id),
  FOREIGN KEY(id_image) REFERENCES pw_images(id)  ON DELETE CASCADE,
  FOREIGN KEY(id_terrain_point) REFERENCES pw_terrain_points(id)
); 

CREATE TABLE pw_cameras (
  id INTEGER,
  name VARCHAR(100),
  lens VARCHAR(100),
  sensor_width DOUBLE,
  sensor_height DOUBLE,
  focal DOUBLE,
  scale_factor DOUBLE,
  PRIMARY KEY (id),
  UNIQUE (name,lens)
);

CREATE TABLE pw_camera_models (
  id INTEGER,
  name VARCHAR(50),
  model_type INTEGER,
  focal DOUBLE,
  id_camera INTEGER,
  xp DOUBLE,
  yp DOUBLE,
  PRIMARY KEY (id),
  FOREIGN KEY(id_camera) REFERENCES pw_cameras(id)  ON DELETE CASCADE
);

CREATE TABLE pw_distortions (
  id INTEGER,
  name VARCHAR(50),
  distortion_type INTEGER,
  xcd DOUBLE,
  ycd DOUBLE,
  kn VARCHAR(700),
  id_camera_model INTEGER,
  PRIMARY KEY (id),
  FOREIGN KEY (id_camera_model) REFERENCES pw_camera_models(id) ON DELETE CASCADE
);

CREATE TABLE pw_models_images (
  id INTEGER,
  id_model INTEGER,
  id_image INTEGER,
  PRIMARY KEY (id),
  UNIQUE (id_model, id_image),
  FOREIGN KEY(id_model) REFERENCES pw_camera_models(id) ON DELETE CASCADE,
  FOREIGN KEY(id_image) REFERENCES pw_images(id) ON DELETE CASCADE
);

CREATE TABLE pw_ext_orient (
  id INTEGER,
  name VARCHAR(50),
  xcp DOUBLE,
  ycp DOUBLE,
  zcp DOUBLE,
  r VARCHAR(500),
  id_image INTEGER,
  FOREIGN KEY (id_image) REFERENCES pw_images(id) ON DELETE CASCADE,
  PRIMARY KEY (id)
);

CREATE TABLE pw_masks (
  id INTEGER,
  wkt_poligon VARCHAR(1000),
  id_image INTEGER,
  PRIMARY KEY (id),
  FOREIGN KEY (id_image) REFERENCES pw_images(id) ON DELETE CASCADE
);