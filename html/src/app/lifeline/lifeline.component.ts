import { Component } from '@angular/core';
import { SettingsService } from '../settings.service';
import { Config } from '../app.config';
import { Observable } from 'rxjs/Observable';
import { Subject } from 'rxjs/Subject';
import { Observer } from 'rxjs/Observer';

@Component({
    selector: 'lifeline',
    template: require('./lifeline.html'),
    styles: [require('./lifeline.scss')]
})
export class LifeLineComponent {
    private lifeline: WebSocket;
    private heartbeat: boolean;

    constructor(private config: Config) {
        // this.create(config.get('lifeline.ws')).subscribe(msg => console.log(msg), error => console.log(error), ()=> console.log('complete'));
    }

    ngAfterViewInit() {
        this.lifeline = new WebSocket(this.config.get('lifeline.ws'));
        this.lifeline.onopen = (evt) => {
            console.log(evt);
        };
        this.lifeline.onmessage = (msg) => {
            console.log('msg ', msg);
            this.heartbeat = !this.heartbeat;
            setTimeout(()=> this.lifeline.send('moe'), 500);
        };
        this.lifeline.onerror = this.onError;
        this.lifeline.onclose = this.onClose;
    }

    private send() {
        this.lifeline.send('moe');

    }

    private onMessage(event: any) {
        console.log('Msg ', event);
    }

    private onError(event: any) {
        console.log('Error ', event);
    }

    private onClose(event: any) {
        console.log('Close ', event);
    }


    private create(url): Subject<MessageEvent> {
        let ws = new WebSocket(url);
        let observable = Observable.create(
            (obs: Observer<MessageEvent>) => {
                ws.onmessage = obs.next.bind(obs);
                ws.onerror = obs.error.bind(obs);
                ws.onclose = obs.complete.bind(obs);
                return ws.close.bind(ws);
            }
        );
        let observer = {
            next: (data: Object) => {
                if (ws.readyState === WebSocket.OPEN) {
                    ws.send(JSON.stringify(data));
                }
            },
        };
        return Subject.create(observer, observable);
    }
}