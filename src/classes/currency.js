// this script is used to track currencies
// "yay short code" - peanut
'use strict';
/* global Decimal */
import { screen, currencies } from '../vars.js';
export class Currency {
  constructor(id) {
    this.id = id;
    this.amount = new Decimal(0);
    this.baseGen = 0; // base generation amount 
    this.multiplier = new Decimal(1); // multiplier of said currency
    currencies.set(this.id, this);
  }

  generate() {
    this.amount = this.amount.plus(this.multiplier.mul(this.baseGen * screen.deltaTime));
  }
}

export function updateCurrencies() {
  currencies.forEach(currency => currency.generate());
}
