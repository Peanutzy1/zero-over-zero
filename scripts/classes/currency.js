// this script is used to track currencies
// "yay short code" - peanut
'use strict';

export class currency {
  constructor(id) {
    this.id = id;
    this.amount = 0;
    this.passiveGeneration = false;
    this.baseGen = 0; // base generation amount 
    this.multiplier = 0; // multiplier of said currency
  }
}
