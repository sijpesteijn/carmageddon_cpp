import { Component } from '@angular/core';
import { SettingsService } from '../settings.service';
import { Config } from '../app.config';

@Component({
    selector: 'lifeline',
    template: require('./lifeline.html'),
    styles: [require('./lifeline.scss')]
})
export class LifeLineComponent {
    private lifeline: WebSocket;

    constructor(private config: Config) {
        this.lifeline = new WebSocket(config.get('lifeline.ws'));
    }

}