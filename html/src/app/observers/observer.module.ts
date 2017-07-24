import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { ObserverService } from './observer.service';
import { TrafficLightObserverComponent } from './traffic-light/traffic-light.component';
import { HttpModule } from '@angular/http';
import { StreamModule } from '../stream/stream.module';

@NgModule({
    imports: [
        CommonModule,
        FormsModule,
        HttpModule,
        StreamModule
    ],
    exports: [
        TrafficLightObserverComponent
    ],
    declarations: [
        TrafficLightObserverComponent
    ],
    providers: [
        ObserverService
    ]
})
export class ObserverModule {

}