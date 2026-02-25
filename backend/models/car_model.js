const db = require('../database');

const car = {
  getAll: function(callback) {
    return db.query('SELECT * FROM car', callback);
  },
  getOne: function(id, callback) {
    return db.query('SELECT * FROM car WHERE id_car=?', [id], callback);
  },
  add: function(car, callback) {
    return db.query(
      'INSERT INTO car(branch, model) VALUES(?,?)',
      [car.branch, car.model],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('DELETE FROM car WHERE id_car=?', [id], callback);
  },
  update: function(id, car, callback) {
    return db.query(
      'UPDATE car SET branch=?, model=? WHERE id_car=?',
      [car.branch, car.model, id],
      callback
    );
  }
};
module.exports = car;
