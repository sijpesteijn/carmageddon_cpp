import { Component } from '@angular/core';



@Component({
    selector: 'lifeline',
    template: require('./lifeline.html'),
    styles: [require('./lifeline.scss')]
})
export class LifeLineComponent {
    private lifeline: WebSocket;

    constructor() {
        this.lifeline = new WebSocket('ws://localhost:1984/lifeline');
    }

}